DROP VIEW  IF EXISTS spritename;
DROP TABLE IF EXISTS character;
DROP TABLE IF EXISTS sprite;
DROP TABLE IF EXISTS tokenitem;
DROP TABLE if EXISTS gameobject;
DROP TABLE IF EXISTS map;
DROP TABLE IF EXISTS backgroundlayer;
DROP TABLE IF EXISTS maplayer;
DROP TABLE IF EXISTS fowlayer;
DROP TABLE IF EXISTS drawinglayer;

CREATE TABLE gameobject (
	id   serial NOT NULL,
	name character varying(100),
	type integer,
	CONSTRAINT gameobject_pkey PRIMARY KEY (id)
);

CREATE TABLE character (
	id    integer REFERENCES gameobject(id) NOT NULL,
	hp    integer,
	maxhp integer,
	CONSTRAINT character_pkey PRIMARY KEY (id)
);

CREATE TABLE tokenitem (
	id           serial not NULL,
	text         character varying(20) UNIQUE,
	path         character varying(120),
	size         integer,
	custom       bool,
	special      bool,
	gameobjectid integer REFERENCES gameobject(id),
	CONSTRAINT tokenitem_pkey PRIMARY KEY (id)
);

CREATE TABLE backgroundlayer (
	id   serial NOT NULL,
	pixmap bytea,
	CONSTRAINT backgroundlayer_pkey PRIMARY KEY (id)
);

CREATE TABLE maplayer (
	id          serial NOT NULL,
	step        integer,
	CONSTRAINT maplayer_pkey PRIMARY KEY (id)
);

CREATE TABLE fowlayer (
	id          serial NOT NULL,
	step        integer,
	CONSTRAINT fowlayer_pkey PRIMARY KEY (id)
);

CREATE TABLE drawinglayer (
	id serial NOT NULL,
	pixmap bytea,
	CONSTRAINT drawinglayer_pkey PRIMARY KEY (id)
);

CREATE TABLE map (
	id                serial NOT NULL,
	windowtitle       character varying(150),
	sceneheight       integer,
	scenewidth        integer,
	backgroundlayerid integer REFERENCES backgroundlayer(id) NOT NULL,
	maplayerid        integer REFERENCES maplayer(id) NOT NULL,
	foWlayerid        integer REFERENCES fowlayer(id) NOT NULL,
	drawingLayerid    integer REFERENCES drawinglayer(id) NOT NULL,
	CONSTRAINT map_pkey PRIMARY KEY (id)
);

CREATE TABLE sprite (
	id                  serial NOT NULL,
	posx                integer,
	posy                integer,
	zvalue              integer,
	tokenitemid         integer REFERENCES tokenitem(id) NOT NULL,
	maplayerid          integer REFERENCES maplayer(id),
	fowlayerid          integer REFERENCES fowlayer(id),
	gameobjectid        integer REFERENCES gameobject(id),
	CONSTRAINT sprite_pkey PRIMARY KEY (id)
);

CREATE VIEW spritename AS
	SELECT sprite.id, text AS name
	FROM sprite 
	JOIN tokenitem ON sprite.tokenitemid = tokenitem.id
;
