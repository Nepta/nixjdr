DROP TABLE IF EXISTS sprite;
DROP TABLE IF EXISTS tokenitem;
DROP TABLE IF EXISTS map;
DROP TABLE IF EXISTS backgroundlayer;
DROP TABLE IF EXISTS maplayer;
DROP TABLE IF EXISTS fowlayer;
DROP TABLE IF EXISTS drawinglayer;

CREATE TABLE tokenitem (
	id      serial not NULL,
	text    character varying(20) UNIQUE,
	path    character varying(120),
	size    integer,
	custom  integer,
	special integer,
	CONSTRAINT tokenitem_pkey PRIMARY KEY (id)
);

CREATE TABLE backgroundlayer (
	id   serial NOT NULL,
	path character varying(120),
	CONSTRAINT backgroundlayer_pkey PRIMARY KEY (id)
);

CREATE TABLE maplayer (
	id          serial NOT NULL,
	CONSTRAINT maplayer_pkey PRIMARY KEY (id)
);

CREATE TABLE fowlayer (
	id          serial NOT NULL,
	CONSTRAINT fowlayer_pkey PRIMARY KEY (id)
);

CREATE TABLE drawinglayer (
	id serial NOT NULL,
	-- TODO pixmap BLOB,
	CONSTRAINT drawinglayer_pkey PRIMARY KEY (id)
);

CREATE TABLE map (
	id                serial NOT NULL,
	sceneheight       integer,
	scenewidth        integer,
-- TODO	backgroundlayerid integer REFERENCES backgroundlayer(id) NOT NULL,
-- TODO	foWlayerid        integer REFERENCES fowlayer(id) NOT NULL,
-- TODO	drawingLayerid    integer REFERENCES drawinglayer(id) NOT NULL,
	backgroundlayerid integer NOT NULL,
	maplayerid        integer REFERENCES maplayer(id) NOT NULL,
	foWlayerid        integer NOT NULL,
	drawingLayerid    integer NOT NULL,
	CONSTRAINT map_pkey PRIMARY KEY (id)
);

CREATE TABLE sprite (
	id                  serial NOT NULL,
	posx                integer,
	posy                integer,
	zvalue              integer,
	tokenitemid         integer REFERENCES tokenitem(id) NOT NULL,
-- TODO	maplayerid          integer REFERENCES maplayer(id),
-- TODO	fowlayerid          integer REFERENCES fowlayer(id),
	maplayerid          integer,
	fowlayerid          integer,
	CONSTRAINT sprite_pkey PRIMARY KEY (id)
);
