DROP TABLE IF EXISTS tokenitem;
DROP TABLE IF EXISTS sprite;
DROP TABLE IF EXISTS map;
DROP TABLE IF EXISTS backgroundlayer;
DROP TABLE IF EXISTS maplayer;
DROP TABLE IF EXISTS fowlayer;
DROP TABLE IF EXISTS gridlayer;
DROP TABLE IF EXISTS drawinglayer;

CREATE TABLE tokenitem (
	id 		serial not NULL,
	name 	character varying(20),
	path 	character varying(120),
	size 	integer,
	CONSTRAINT tokenitem_pkey PRIMARY KEY (id)
);

CREATE TABLE backgroundlayer (
	id 		serial NOT NULL,
	path 	character varying(120),
	CONSTRAINT backgroundlayer_pkey PRIMARY KEY (id)
);

CREATE TABLE gridlayer (
	id 			serial NOT NULL,
	tilesize 	integer,
	CONSTRAINT gridlayer_pkey PRIMARY KEY (id)
);

CREATE TABLE maplayer (
	id 				serial NOT NULL,
	gridlayerid 	integer REFERENCES gridlayer(id),
	CONSTRAINT maplayer_pkey PRIMARY KEY (id)
);

CREATE TABLE fowlayer (
	id 				serial NOT NULL,
	gridlayerid 	integer REFERENCES gridlayer(id),
	CONSTRAINT fowlayer_pkey PRIMARY KEY (id)
);

CREATE TABLE drawinglayer (
	id serial NOT NULL,
	-- TODO add pixmap
	CONSTRAINT drawinglayer_pkey PRIMARY KEY (id)
);

CREATE TABLE map (
	id serial NOT NULL,
	backgroundlayerid	integer	REFERENCES backgroundlayer(id),
	maplayerid 			integer	REFERENCES maplayer(id),
	foWlayerid 			integer	REFERENCES fowlayer(id),
	drawingLayerid 		integer	REFERENCES drawinglayer(id),
	sceneheight 		integer,
	scenewidth			integer,
	CONSTRAINT map_pkey PRIMARY KEY (id)
);

CREATE TABLE sprite (
	id 				serial NOT NULL,
	gridlayerid 	integer REFERENCES gridlayer(id),
	posx			integer,
	posy 			integer,
	path 			character varying(120),
	CONSTRAINT sprite_pkey PRIMARY KEY (id)
);
