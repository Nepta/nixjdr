#!/bin/bash
psql -U jdr -W -d jdrdb < initTables.sql
psql -U jdr -W -d jdrdb < initRows.sql
