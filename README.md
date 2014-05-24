nixjdr
======

Creation of a graphical and interactive interface for tabletop role-playing game (like Dungeons and Dragons, Pathfinder etc.)

dependencies
------------
Need postgresql for QPSQL driver to work

HOW TO
======
for now, you need to have a postgresql database installed with this configuration:
role (user): "jdr"
password: "password"
database name: "jdrDB"

and for the token list you must have a table named "sprite"
create table sprite (id serial primary key, name varchar(20), path varchar(120), size integer);
you can use resource/spriteInsert.sql to help populate the table
