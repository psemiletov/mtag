# mtag

EN: mtag is the command-line tool for media files tagging. It can use the text file template to tag the multiply sets of media files. You can use just one template for Ogg, MP3, and FLAC album versions. 

To be tagged correctly, the media files names needs to be named in the alphabetical order, i.e. for example:

01-first-song.ogg 
01-second-song.ogg 
01-third-song.ogg 

RU: mtag это утилита для записи тэгов в мультимедийные файлы. mtag использует файл-шаблон с тэгами, который можно применять к нескольким наборам файлов в разных форматах. Иначе говоря, одним шаблоном вы запишете тэги в варианты альбома в MP3, Ogg, FLAC. Файлы должны быть именованы по алфавиту, например:

01-first-song.ogg 
01-second-song.ogg 
01-third-song.ogg 


Usage:
------------

EN:

mtag rules_file extension

Example: mtag rules.txt ogg

The rules file must be in UTF-8 encoding. The rules file syntax is simple - the set of blocks with tags. Each block is ended with "\#\#\#". Example:

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

The list of available tags: @artist, @title, @album, @genre, @comment, @year, @track.

RU:

mtag файл_с_правилами расширение

Пример: mtag rules.txt ogg

Файл правил должен быть в кодировке UTF-8. Синтаксис файла прост - файл состоит из блоков тэгов, и каждый блок оканчивается "\#\#\#". Пример:

@album=проба
@artist=никто
@title=песенка первая
\#\#\#

@album=проба
@artist=никто
@title=песенка вторая
\#\#\#

@album=testalbum
@artist=никто
@title=песня третья
\#\#\#

Первый блок будет применен к первому файлу (с указанным расширением) в текущем каталоге, второй ко второму, и так далее.

Список доступных тэгов: @artist, @title, @album, @genre, @comment, @year, @track.

Requirements:
------------

Taglib, C++ 11

Installation:
------------

EN:

As usual, under the root (mtag will be installed to /usr/local/bin):

make
make install

To uninstall:

make uninstall


RU:

Как обычно, под рутом (mtag будет установлен в /usr/local/bin):

make
make install

А чтобы удалить:

make uninstall


License/Лицуха
-----------

EN: mtag is public domain.

RU: mtag - общественное достояние.


License/Лицуха
-----------

EN: mtag is public domain.

RU: mtag - общественное достояние.


Credits/Кредиты
------------

Program site/сайт: https://github.com/psemiletov/mtag

Developers/разработчики:
Petr Semiletov <tea@list.ru>, http://semiletov.org

