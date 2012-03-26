In order to get this working you will need 2 things in  addition to common Qt SDK installation. I'm using Windows to develop btw.

QXmpp library with some improvements, which I'm using can be downloaded from here: https://github.com/0xd34df00d/qxmpp-dev. See additional info on how to make it run.
Take a look at .pro files of my app, where you will need to edit the paths to the built QXmpp files.
I've managed to use the library only for MeeGo so far, so keep that in mind if you try to run this app on a mobile device. 

QPSQL driver. To get this working, I've used this tutorial: http://briolidz.wordpress.com/2011/11/20/postgresql-driver-for-windows-and-linux/.
I'm using the Postgis extension for PostgreSQL. More info here: http://postgis.refractions.net/.

