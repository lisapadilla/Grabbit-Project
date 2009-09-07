<?php
/**
 * The core of the OpenInviter system
 * 
 * Contains methods and properties used by all
 * the OpenInivter plugins
 * 
 * @author OpenInviter
 * @version 1.7.6
 */
class OpenInviter
	{
	public $pluginTypes=array('email'=>'Email Providers','social'=>'Social Networks');
	private $ignoredFiles=array('default.php'=>'','index.php'=>'');
	private $version='1.7.9';
	private $configStructure=array(
		'username'=>array('required'=>true,'default'=>''),
		'private_key'=>array('required'=>true,'default'=>''),
		'message_body'=>array('required'=>false,'default'=>''),
		'message_subject'=>array('required'=>false,'default'=>''),
		'cookie_path'=>array('required'=>true,'default'=>''),
		'local_debug'=>array('required'=>false,'default'=>false),
		'remote_debug'=>array('required'=>false,'default'=>false),
		'hosted'=>array('required'=>false,'default'=>false),
		'proxies'=>array('required'=>false,'default'=>array()),
		'stats'=>array('required'=>false,'default'=>false),
		'stats_user'=>array('required'=>false,'default'=>''),
		'stats_password'=>array('required'=>false,'default'=>''),
	);
	private $statsDB=false;
	
	public function __construct()
		{
		include(dirname(__FILE__)."/config.php");
		include_once(dirname(__FILE__)."/openinviter_base.php");
		$this->settings=$openinviter_settings;
		}
	
	private function checkConfig()
		{
		$to_add=array();$ok=true;
		foreach ($this->configStructure as $option=>$details)
			{
			if (!isset($this->settings[$option])) $to_add[$option]=$details['default'];
			if ($ok) if ($details['required'] AND empty($this->settings[$option])) { $this->internalError="`{$option}` is not defined in config.php";$ok=false; }
			}
		if (!empty($to_add))
			{
			$file_path=dirname(__FILE__)."/config.php";
			if (is_writable($file_path))
				{
				foreach ($to_add as $option=>$value) $this->settings[$option]=$value;
				$file_contents="<?php\n";
				$file_contents.="\$openinviter_settings=array(\n".$this->arrayToText($this->settings)."\n);\n";
				$file_contents.="?>";
				file_put_contents($file_path,$file_contents);
				}
			}
		return $ok;
		}
	
	private function arrayToText($array)
		{
		$text='';
		$flag=false;
		$i=0;
		foreach ($array as $key=>$val)
			{
			if($flag) $text.=",\n";
			$flag=true;
			$text.="'{$key}'=>";
			if (is_array($val)) $text.='array('.$this->arrayToText($val).')';
			elseif (is_bool($val)) $text.=($val?'true':'false');
			else $text.="\"{$val}\"";
			}
		return($text);
		}
	
	private function statsCheck()
		{
		if (!$this->settings['stats']) return true;
		$db_file=dirname(__FILE__).'/openinviter_stats.sqlite';
		if (!file_exists($db_file))
			{
			if (!is_writable(dirname(__FILE__))) { $this->internalError="Unable to write stats. ".dirname(__FILE__)." is not writable";return false; }
			if (!$this->statsOpenDB()) { $this->internalError="Unable to create the stats database.";return false; }
			$this->statsQuery("CREATE TABLE oi_imports (id INTEGER PRIMARY KEY, service VARCHAR(16), contacts INTEGER, insert_dt DATETIME, insert_ip VARCHAR(15))");
			$this->statsQuery("CREATE TABLE oi_messages (id INTEGER PRIMARY KEY, service VARCHAR(16), type CHAR(1), messages INTEGER, insert_dt DATETIME, insert_ip VARCHAR(15))");
			}
		elseif (!is_readable($db_file)) { $this->internalError="Unable to open stats database. {$db_file} is not readable.";return false; }
		elseif (!is_writable($db_file)) { $this->internalError="Unable to write stats. {$db_file} is not writable";return false; }
		elseif (!$this->statsOpenDB()) { $this->internalError="Unable to open the stats database.";return false; }
		return true;
		}
	
	private function statsOpenDB()
		{
		if (!$this->settings['stats']) return true;
		if ($this->statsDB=sqlite_open(dirname(__FILE__).'/openinviter_stats.sqlite',0666)) return true;
		return false;
		}
	
	private function statsRecordImport($contacts)
		{
		if (!$this->settings['stats']) return true;
		if (!$this->statsDB) if (!$this->statsOpenDB()) return false;
		$this->statsQuery("INSERT INTO oi_imports (service,contacts,insert_dt,insert_ip) VALUES ('{$this->plugin->service}','{$contacts}','".date("Y-m-d H:i:s")."','{$_SERVER['REMOTE_ADDR']}')");
		}
	
	private function statsRecordMessages($msg_type,$messages)
		{
		if (!$this->settings['stats']) return true;
		if (!$this->statsDB) if (!$this->statsOpenDB()) return false;
		$this->statsQuery("INSERT INTO oi_messages (service,type,messages,insert_dt,insert_ip) VALUES ('{$this->plugin->service}','{$msg_type}','{$messages}','".date("Y-m-d H:i:s")."','{$_SERVER['REMOTE_ADDR']}')");
		}
	
	public function statsQuery($query)
		{
		if (!$this->settings['stats']) return false;
		if (!$this->statsDB)
			{
			if (!$this->statsCheck()) return false;
			if (!$this->statsOpenDB()) return false;
			}
		return sqlite_query($this->statsDB,$query,SQLITE_ASSOC);		
		}
	
	/**
	 * Start internal plugin
	 * 
	 * Starts the internal plugin and
	 * transfers the settings to it.
	 * 
	 * @param string $plugin_name The name of the plugin being started
	 */	  
	public function startPlugin($plugin_name,$getPlugins=false)
		{
		if (file_exists(dirname(__FILE__)."/postinstall.php")) { $this->internalError="You have to delete postinstall.php before using OpenInviter";return false; }
		elseif ($this->settings['hosted'])
			{
			if (!file_exists(dirname(__FILE__)."/plugins/_hosted.php")) $this->internalError="Invalid service provider";
			else
				{
				if (!class_exists('_hosted')) include_once(dirname(__FILE__)."/plugins/_hosted.php");
				if ($getPlugins)
					{
					$this->servicesLink=new _hosted($plugin_name);
					$this->servicesLink->settings=$this->settings;
					$this->servicesLink->base_version=$this->version;
					$this->servicesLink->base_path=dirname(__FILE__);
					}
				else
					{
					if (!$this->checkConfig()) return false;
					if (!$this->statsCheck()) return false;
					$this->plugin=new _hosted($plugin_name);
					$this->plugin->settings=$this->settings;
					$this->plugin->base_version=$this->version;
	    			$this->plugin->base_path=dirname(__FILE__);
	    			$this->plugin->hostedServices=$this->getPlugins();
					}
				}
			}
		elseif (file_exists(dirname(__FILE__)."/plugins/{$plugin_name}.php"))
			{
			$ok=true;
			if (!class_exists($plugin_name)) include_once(dirname(__FILE__)."/plugins/{$plugin_name}.php");
			if (!$this->checkConfig()) return false;
			if (!$this->statsCheck()) return false;
			$this->plugin=new $plugin_name();
    		$this->plugin->settings=$this->settings;
    		$this->plugin->base_version=$this->version;
    		$this->plugin->base_path=dirname(__FILE__);
			if (file_exists(dirname(__FILE__)."/conf/{$plugin_name}.conf")) 
				{
				include(dirname(__FILE__)."/conf/{$plugin_name}.conf");
				if (empty($enable)) $this->internalError="Invalid service provider";
				if (!empty($messageDelay)) $this->plugin->messageDelay=$messageDelay; else  $this->plugin->messageDelay=1;
				if (!empty($maxMessages)) $this->plugin->maxMessages=$maxMessages; else $this->plugin->maxMessages=10;
				}
			}
		else { $this->internalError="Invalid service provider";return false; }
		return true;
		}
	
	/**
	 * Stop the internal plugin
	 * 
	 * Acts as a wrapper function for the stopPlugin
	 * function in the OpenInviter_Base class
	 */
	public function stopPlugin($graceful=false)
		{
		$this->plugin->stopPlugin($graceful);
		}

	/**
	 * Login function
	 * 
	 * Acts as a wrapper function for the plugin's
	 * login function.
	 * 
	 * @param string $user The username being logged in
	 * @param string $pass The password for the username being logged in
	 * @return mixed FALSE if the login credentials don't match the plugin's requirements or the result of the plugin's login function.
	 */
	public function login($user,$pass)
		{
	//	if (!$this->checkLoginCredentials($user)) return false;
		return $this->plugin->login($user,$pass);
	//	}
	
	/**
	 * Get the current user's contacts
	 * 
	 * Acts as a wrapper function for the plugin's
	 * getMyContacts function.
	 * 
	 * @return mixed The result of the plugin's getMyContacts function.
	 */
	public function getMyContacts()
		{
		$contacts=$this->plugin->getMyContacts();
		if ($contacts!==false) $this->statsRecordImport(count($contacts));
		return $contacts;
		}	

	/**
	 * End the current user's session
	 * 
	 * Acts as a wrapper function for the plugin's
	 * logout function
	 * 
	 * @return bool The result of the plugin's logout function.
	 */
	public function logout()
		{
		return $this->plugin->logout();	
		}

	/**
	 * Get the installed plugins
	 * 
	 * Returns information about the available plugins
	 * 
	 * @return mixed An array of the plugins available or FALSE if there are no plugins available.
	 */
	 
	public function writePlConf($name_file,$type)
		{
		if (!file_exists(dirname(__FILE__)."/conf")) mkdir(dirname(__FILE__)."/conf",0755,true);
		if ($type=='social')  file_put_contents(dirname(__FILE__)."/conf/{$name_file}.conf",'<?php $enable=true;$autoUpdate=true;$messageDelay=1;$maxMessages=10;?>');	
		elseif($type=='email') file_put_contents(dirname(__FILE__)."/conf/{$name_file}.conf",'<?php $enable=true;$autoUpdate=true; ?>');
		elseif($type=='hosted') file_put_contents(dirname(__FILE__)."/conf/{$name_file}.conf",'<?php $enable=false;$autoUpdate=true; ?>');		
		}
	 
	public function getPlugins($update=false)
		{
		$plugins=array();$array_file=array();
		$dir=dirname(__FILE__)."/plugins";
		$temp=glob("{$dir}/*.php");$using_hosted=false;
        foreach ($temp as $file) if (($file!=".") AND ($file!="..") AND (!isset($this->ignoredFiles[str_replace("{$dir}/",'',$file)]))) $array_file[$file]=$file;
        if ($update==false)
        	{
	        if ($this->settings['hosted'])
	        	{
				$using_hosted=true;$has_services=false;
				$path=$this->settings['cookie_path'].'/oi_hosted_services.txt';
				if (file_exists($path))
					if (time()-filemtime($path)<=0) $has_services=true;
				if ($has_services) $plugins['email']=unserialize(file_get_contents($path));
				else
					{
					if ($this->startPlugin('_hosted',true))
						if (!$temp=$this->servicesLink->getHostedServices()) $plugins=array();
						else
							{
							file_put_contents($path,$temp);
							$plugins['email']=unserialize($temp);
							}
					}
	        	}
        	}
        if (!$update)
        	{
        	$path=dirname(__FILE__).'/plugins/_hosted.php';
        	if (isset($array_file[$path])) unset($array_file[$path]);
        	}
        if ($update==TRUE OR $this->settings['hosted']==FALSE)
			if (count($array_file)>0) 
				{
				sort($array_file);
				foreach($array_file as $key=>$file)
					{
					$val=str_replace("{$dir}/",'',$file);
					$plugin_key=str_replace('.php','',$val);
					if (file_exists(dirname(__FILE__)."/conf/{$plugin_key}.conf"))
						{
						include_once(dirname(__FILE__)."/conf/{$plugin_key}.conf");
						if ($enable AND $update==false)
							{ include("{$dir}/{$val}");if ($this->checkVersion($_pluginInfo['base_version'])) $plugins[$_pluginInfo['type']][$plugin_key]=$_pluginInfo;	}
						elseif ($update==true)
							{ include("{$dir}/{$val}"); if ($this->checkVersion($_pluginInfo['base_version'])) $plugins[$_pluginInfo['type']][$plugin_key]=array_merge(array('autoupdate'=>$autoUpdate),$_pluginInfo); }
						}
					else
						{  include("{$dir}/{$val}");if ($this->checkVersion($_pluginInfo['base_version'])) $plugins[$_pluginInfo['type']][$plugin_key]=$_pluginInfo; $this->writePlConf($plugin_key,$_pluginInfo['type']);}
					}
				}
		return $plugins;
		}
	
	/**
	 * Send a message
	 * 
	 * Acts as a wrapper for the plugin's
	 * sendMessage function.
	 * 
	 * @param string $session_id The OpenInviter user's session ID
	 * @param string $message The message being sent to the users
	 * @param array $contacts An array of contacts that are going to receive the message
	 * @return mixed -1 if the plugin doesn't have an internal sendMessage function or the result of the plugin's sendMessage function
	 */
	public function sendMessage($session_id,$message,$contacts)
		{
		$this->plugin->init($session_id);
		$internal=$this->getInternalError();
		if ($internal) return false;
		if (!method_exists($this->plugin,'sendMessage')) { $this->statsRecordMessages('E',count($contacts));return -1; }
		else 
			{
			$sent=$this->plugin->sendMessage($session_id,$message,$contacts);
			if ($sent!==false) $this->statsRecordMessages('I',count($contacts));
			return $sent;
			}
		}
	
	/**
	 * Find out if the contacts should be displayed
	 * 
	 * Tells whether the current plugin will display
	 * a list of contacts or not
	 * 
	 * @return bool TRUE if the plugin displays the list of contacts, FALSE otherwise.
	 */
	public function showContacts()
		{
		return $this->plugin->showContacts;
		}
	
	/**
	 * Check version requirements
	 * 
	 * Checks if the current version of OpenInviter
	 * is greater than the plugin's required version
	 * 
	 * @param string $required_version The OpenInviter version that the plugin requires.
	 * @return bool TRUE if the version if equal or greater, FALSE otherwise.
	 */
	public function checkVersion($required_version)
		{
		if (version_compare($required_version,$this->version,'<=')) return true;
		return false;
		}
	
	/**
	 * Find out the version of OpenInviter
	 * 
	 * Find out the version of the OpenInviter
	 * base class
	 * 
	 * @return string The version of the OpenInviter base class.
	 */
	public function getVersion()
		{
		return $this->version;
		}
	
	/**
	 * Check the provided login credentials
	 * 
	 * Checks whether the provided login credentials
	 * match the plugin's required structure and (if required)
	 * if the provided domain name is allowed for the
	 * current plugin.
	 * 
	 * @param string $user The provided user name.
	 * @return bool TRUE if the login credentials match the required structure, FALSE otherwise. 
	 */
	private function checkLoginCredentials($user)
		{
		$is_email=$this->plugin->isEmail($user);
		if ($this->plugin->requirement)
			{
			if ($this->plugin->requirement=='email' AND !$is_email)
				{
				$this->internalError="Please enter the full email, not just the username";
				return false;
				}
			elseif ($this->plugin->requirement=='user' AND $is_email)
				{
				$this->internalError="Please enter just the username, not the full email";
				return false;
				}
			}
		if ($this->plugin->allowed_domains AND $is_email)
			{
			$temp=explode('@',$user);$user_domain=$temp[1];$temp=false;
			foreach ($this->plugin->allowed_domains as $domain)
				if (strpos($user_domain,$domain)!==false) $temp=true;
			if (!$temp)
				{
				$this->internalError="<b>{$user_domain}</b> is not a valid domain for this provider";
				return false;
				}
			}
		return true;
		}
	
	/**
	 * Gets the OpenInviter's internal error
	 * 
	 * Gets the OpenInviter's base class or the plugin's
	 * internal error message
	 * 
	 * @return mixed The error message or FALSE if there is no error.s
	 */
	public function getInternalError()
		{
		if (isset($this->internalError)) return $this->internalError;
		if (isset($this->plugin->internalError)) return $this->plugin->internalError;
		return false;
		}
	
	/**
	 * Get the current OpenInviter session ID
	 * 
	 * Acts as a wrapper function for the plugin's
	 * getSessionID function.
	 * 
	 * @return mixed The result of the plugin's getSessionID function.
	 */
	public function getSessionID()
		{
		return $this->plugin->getSessionID();
		}
	
	}
	
	
?>