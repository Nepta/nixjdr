#!/bin/bash
psql -U jdr -W -d jdrdb < initTables.sql
