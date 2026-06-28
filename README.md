# Cashmere Database

This is a personal C project I am building to track cashmere sweaters, fabric pieces, notes, and lookup data.

The main idea is simple: I work with cashmere sweaters and wanted a database for keeping track of them. Instead of making a basic script or spreadsheet, I decided to turn it into a real C client/server project with sockets, packets, SQLite, serialization, and CRUD operations.

This project is mostly about building something useful while learning how lower-level systems actually fit together.

## What It Does

Cashmere Database lets a client program send database requests to a server program. The server receives the request, reads the packet, decodes the payload, runs the correct SQLite operation, and sends a response back to the client.

The database tracks things like:

* Sweaters
* Fabric pieces cut from sweaters
* Notes
* Brands
* Colors
* Sizes
* Conditions
* Necklines
* Sleeves
* Garment types
* Piece types

## Why I Built This

I wanted a project that was more interesting than a normal tutorial app.

This project gives me a reason to practice:

* C programming
* Socket networking
* Custom packet design
* Serialization and deserialization
* SQLite database work
* CRUD operations
* File parsing
* Project organization
* Debugging real program flow

It is also connected to something real I actually care about, which makes it easier to keep building.

## Tech Used

* C
* SQLite3
* POSIX sockets
* Make
* Linux

## How It Works

The project has two main programs:

* `server` — owns the database and handles requests
* `client` — asks the user questions, builds requests, and sends them to the server

The client and server communicate using a custom packet format.

Each packet has a fixed-size header:

```c
packet_type
request_type
packet_status
payload_length
```

After the header, the packet contains a payload string. The server reads the header first, then reads the payload based on `payload_length`.

The payload is encoded and decoded depending on what table is being used.

Example idea:

```text
TABLE=BRAND ID=0 BRAND=J_Crew
```

## Database

The database uses SQLite.

Main record tables:

* `SWEATER`
* `PIECE`
* `NOTE`

Lookup tables:

* `BRAND`
* `COLOR_FAMILY`
* `COLOR`
* `NECKLINE`
* `SLEEVES`
* `TYPE`
* `CONDITION`
* `SIZE`
* `PIECE_TYPE`

The lookup tables help keep the main sweater records cleaner and more consistent.

## Current Features

* Client/server connection
* Custom packet structure
* Packet serialization/deserialization
* Send-all and receive-all network helpers
* SQLite database initialization
* Create operations for database records
* Read-by-ID functions for lookup tables
* Payload encode/decode helpers
* Seed files for lookup data
* Basic terminal menu

## In Progress

* Full read/search flow
* Update records
* Delete records
* Import records
* Export records
* Better terminal UI
* Cleaner error handling
* More testing

## Project Structure

```text
.
├── data/
│   ├── database_init.sql
│   └── seeds/
├── lib/
│   ├── constants.h
│   ├── database.h
│   ├── db_tables.h
│   ├── network.h
│   ├── packet.h
│   └── payload.h
├── src/
│   ├── client.c
│   ├── server.c
│   ├── database.c
│   ├── network.c
│   ├── packet.c
│   ├── payload.c
│   └── seed.c
└── makefile
```

## Build

```bash
make
```

Or build the client and server separately:

```bash
make c
make s
```

## Run

Start the server:

```bash
./build/server
```

Start the client in another terminal:

```bash
./build/client
```

## Notes

This project is intentionally kept simple.

I am not trying to make a huge enterprise inventory system. I am trying to build a real working C project that teaches me how the pieces connect:

```text
user input -> client request -> packet -> socket -> server -> SQLite -> response
```

The goal is to keep improving it piece by piece while keeping the code understandable.
