<?php
// $Id$

/**
 * @file brightcove-cck-player.tpl.php
 * Default theme implementation to play Brightcove video.
 *
 * This template is used when viewing a Brightcove video with a default
 * formatter, standard video player.
 *
 * Available variables:
 *   - $player: Video player HTML code.
 *   - $video_id: Video ID from Media API.
 *
 * @see theme_brightcove_cck_formatter_default()
 */
?>

<?php if ($player): ?>
<?php echo $player; ?>
<?php endif; ?>
