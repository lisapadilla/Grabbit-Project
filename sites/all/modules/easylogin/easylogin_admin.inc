<?php

function easylogin_hash($userid){
  // turn a realistically blind eye to collisions
  return sha1($userid . drupal_get_private_key() . easylogin_salt());
}

function easylogin_salt(){
  return md5(uniqid(mt_rand(), true)) . md5(uniqid(mt_rand(), true));
}