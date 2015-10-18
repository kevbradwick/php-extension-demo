--TEST--
Change the greeting
--SKIPIF--
<?php if (!extension_loaded("demo_ext")) print "skip"; ?>
--FILE--
<?php
echo greeting_alt('Yo', 'Hey');
?>
--EXPECT--
Hey Yo!
