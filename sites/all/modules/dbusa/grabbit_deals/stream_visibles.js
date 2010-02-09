/**
  [ Stream Visibles ]
  Executes a callback function on the items currently visible on an item stream,
  after a timeout period specified by the timeout variable
  
  Rafael Cardenas <rcardenas@daniloblackusa.com>
  
  Example:
  
  $(document).ready(function()
  {
    streamVisibles('#stream', '.item', callbackFunc, 1500);
  });

  function callbackFunc(item)
  {
    $(item).css('background-color','#DDDDDD');
  }
*/

function streamVisibles(stream, item, callback, timeout)
{
  // manage stream scrolling events
  var timer;
  var streamh = $(stream).height();
  
  // engage visibles for the first time
  engageVisibles(stream, item, callback, streamh);
  
    $(stream).scroll(function()
    { 
      // timer for recalculation
      if ( timer != null ) clearTimeout( timer );
      timer = setTimeout( "engageVisibles('"+stream+"','"+item+"',"+callback+","+streamh+")", timeout );
    });  
  
  
}

function firstVisibles(stream, item, callback)
{
  // engage visibles for the first time
  var streamh = $(stream).height();
  engageVisibles(stream, item, callback, streamh);
}

function engageVisibles(stream, item, callback, streamh)
{ 
  // loop through items to find visibles
  $(item, stream).each(function()
  {
    // item properties
    var pos     = $(this).position().top;
    var height  = $(this).height();
    
    // full visibility condition, execute callback action
    if ( pos >= 0 && pos <= streamh - height && $(this).attr('engaged') != 'true' )
    {
      callback(this);
      $(this).attr('engaged','true');
    }
  });
}
