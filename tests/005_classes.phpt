--TEST--
Change the greeting
--SKIPIF--
<?php if (!extension_loaded("demo_ext")) print "skip"; ?>
--FILE--
<?php
var_dump(class_exists("Greeting"));
?>
--EXPECT--
bool(true)
