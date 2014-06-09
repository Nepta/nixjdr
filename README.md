nixjdr
======

Creation of a graphical and interactive interface for tabletop role-playing game (like Dungeons and Dragons, Pathfinder etc.)

##Dependencies
PostgreSQl is needed by the QPSQL driver.

##HOW TO
####PostgreSQL configuration
role (user): "jdr"  
password: "password"  
database name: "jdrdb"

####Database initialisation
Run resource/Queries/init.sh (requires PostgreSQL password authentication, [link](http://stackoverflow.com/questions/18664074/getting-error-peer-authentication-failed-for-user-postgres-when-trying-to-ge)), or execute the queries contained in resource/Queries/initTables.sql and resource/Queries/initRows.sql.
