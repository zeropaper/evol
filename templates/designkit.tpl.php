<!-- 
- compiled_filepath: <?php print $compiled_filepath; ?>

<?php print $debug; ?>

- no_style: <?php print isset($no_style); ?> / <?php print $no_style; ?>
-->


<?php if ($compiled_filepath) { ?>
<link type="text/css" rel="stylesheet" media="all" href="<?php print check_url(file_create_url($compiled_filepath)); ?>" />
<?php } ?>


<?php if (!isset($no_style) || !$no_style) { ?>
<style type='text/css'>
/* Color coding */
<?php print $color_coding; ?>


/* Added CSS code */
<?php print $added; ?>
</style>
<?php } ?>
