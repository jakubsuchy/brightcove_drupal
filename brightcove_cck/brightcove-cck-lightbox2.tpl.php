<?php
// $Id$

/**
 * @file brightcove-cck-lightbox2.tpl.php
 * Image -> Lightbox2 player theme implementation.
 *
 * This template is used when viewing a Brightcove video with a thumbnail or videoStill image linking to Lightbox2.
 *
 * Available variables:
 *   - $output: Formatted image with a link to Lightbox2, ready for printing.
 *   - $video_width: Real video width.
 *   - $video_height: Real video height.
 *   - $lightbox2_width: Lightbox2 window width.
 *   - $lightbox2_height: Lightbox2 window height.
 *   - $image_field: The name of the image field used from Media API. Can be thumbnailURL or videoStillURL.
 *   - $destination: URL for the Brightcove video player.
 *   - $video_id: Video ID from Media API.
 *   - $field_name: CCK Field name.
 *   - $type_name: Node type.
 *   - $preset: If printed with imagecache, Imagecache preset name.
 *
 * @see theme_brightcove_cck_lightbox2_player()
 */
?>

<?php if ($output): ?>
<?php echo $output; ?>
<?php endif; ?>
<?php
