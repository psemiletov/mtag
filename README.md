# mtag

mtag is the command-line tool for media files tagging. It can use the text file template to tag the multiply sets of media files. You can use just one template for Ogg, MP3, and FLAC album versions. 

To be tagged correctly, the media files names needs to be named in the alphabetical order, i.e. for example:

01-first-song.ogg 
01-second-song.ogg 
01-third-song.ogg 

Usage:
------------

mtag rules_file extension

Example: mtag rules.txt .ogg

The rules file syntax is simple. The file MUST has the header line "; <optional text>", and then the set of blocks with tags. Each block is ended with "\#\#\#".

Example:

@album=testalbum
@artist=Megapunkers
@title=song one
\#\#\#

@album=testalbum
@artist=Megapunkers
@title=song two
\#\#\#

@album=testalbum
@artist=Megapunkers
@title=song three
\#\#\#

So the first block will be applied to the first media file at the current directory, the second block to the second file, etc.

Requirements:
------------

Taglib, C++ 11

Installation
------------

make



Other
------------
