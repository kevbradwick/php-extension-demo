--TEST--
Change the greeting
--SKIPIF--
<?php if (!extension_loaded("demo_ext")) print "skip"; ?>
--FILE--
<?php
echo demo_ext_greeting2('Yo', 'Hey');
?>
--EXPECT--
Hey Yo!
