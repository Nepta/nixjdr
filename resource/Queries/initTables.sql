DROP TABLE map;
CREATE TABLE map (
	id serial NOT NULL,
	path character varying(80),
	tilesize integer,
	CONSTRAINT map_pkey PRIMARY KEY (id)
);
	
DROP TABLE sprite;
CREATE TABLE sprite (
	id serial NOT NULL,
	name character varying(20),
	path character varying(120),
	size integer,
	CONSTRAINT sprite_pkey PRIMARY KEY (id)
);
