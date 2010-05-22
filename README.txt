Brightcove integration API and CCK field. Features:

* Browse videos coming from Brightcove Studio directly in Drupal with a possibility to search in videos by name or tags.
* Upload a video for Brightcove customers with at least a Professional account (You need a Write API key).
* Integrates with Views module - creates fields with a video player, all available metadata such as Plays count or Creation dates.
* Provides various formatters including a Lightbox2 player and Imagecache integration for remote images. 


Requirements
------------

CCK: http://drupal.org/project/cck
ModalFrame API: http://drupal.org/project/modalframe
jQuery UI: http://drupal.org/project/jquery_ui
External libraries: Echove Brightcove Framework, http://echove.net


Installation instructions
-------------------------

Get Read and/or Write API keys from Brightcove support. Refer to section Brightcove Keys if you don't know how to do that.

Download module from http://drupal.org/project/brightcove, untar to sites/all/modules or sites/sitename.com/modules

Download Echove framework from http://echove.net/, module is tested with Echove 1.0.9 and later.

Unzip framework to sites/all/libraries/echove. After unzipping, there needs to be a file at sites/all/libraries/echove/echove.php.

Enable Brightcove module and Brightcove CCK Field module at your site.

Navigate to admin/settings/brightcove and fill in your Read/Write key and default Player ID from Brightcove Studio (Refer to section Brightcove player if you don't know how to do that)

Create a new CCK field called of type Brightcove video.

Play.


Brightcove Keys
---------------

To be written, target version: Release Candidate.

Brightcove player
-----------------

To be written, target version: Release Candidate.

Media Mover Integration
-----------------------

To be written, target version: Release Candidate.


