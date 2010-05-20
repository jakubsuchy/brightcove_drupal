<?php
// $Id$

/**
 * @file brightcove-cck-node-link.tpl.php
 * Image linked to node theme implementation.
 *
 * This template is used when viewing a Brightcove video with a thumbnail or videoStill image linking to node.
 *
 * Available variables:
 *   - $output: Formatted image with a link to Lightbox2, ready for printing.
 *   - $image_field: The name of the image field used from Media API. Can be thumbnailURL or videoStillURL.
 *   - $destination: URL for the Brightcove video player.
 *   - $video_id: Video ID from Media API.
 *   - $field_name: CCK Field name.
 *   - $type_name: Node type.
 *   - $preset: If printed with imagecache, Imagecache preset name.
 *
 * @see theme_brightcove_cck_node_link()
 */
?>

<?php if ($output): ?>
<?php echo $output; ?>
<?php endif; ?>
<?php
