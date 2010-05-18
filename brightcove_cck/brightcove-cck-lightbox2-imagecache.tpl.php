<?php
// $Id$

/**
 * @file brightcove-cck-lightbox2-imagecache.tpl.php
 * Imagecache image -> Lightbox2 player theme implementation.
 *
 * This template is used when viewing a Brightcove video with a thumbnail or
 * videoStill image displayed using Imagecache and linking to Lightbox2.
 * Output is created using brightcove-cck-lightbox2.tpl.php file.
 *
 * Available variables:
 *   - $output: Formatted image with a link to Lightbox2, ready for printing.
 *   - $video_id: Video ID from Media API.
 *   - $imagecache_preset: Imagecache preset.
 *
 * @see template_preprocess_brightcove_cck_lightbox2_player()
 * @see brightcove-cck-lightbox2.tpl.php
 */
?>

<?php if ($output): ?>
<?php echo $output; ?>
<?php endif; ?>
