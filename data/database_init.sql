PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS piece_type (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    piece_type TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS brand (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    brand TEXT NOT NULL UNIQUE
);

CREATE TABLE color_family (
    id INTEGER PRIMARY KEY,
    color_family TEXT UNIQUE NOT NULL
);

CREATE TABLE color (
    id INTEGER PRIMARY KEY,
    color_family_id INTEGER NOT NULL,
    color TEXT UNIQUE NOT NULL,
    FOREIGN KEY (color_family_id) REFERENCES color_family(id)
);

CREATE TABLE IF NOT EXISTS neckline (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    neckline TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS sleeves (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    sleeves TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS type (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    type TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS condition (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    condition TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS size (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    size TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS sweater (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    cashmere_code TEXT NOT NULL,
    brand_id INTEGER NOT NULL,
    color_id INTEGER NOT NULL,
    neckline_id INTEGER NOT NULL,
    sleeves_id INTEGER NOT NULL,
    type_id INTEGER NOT NULL,
    condition_id INTEGER NOT NULL,
    size_id INTEGER NOT NULL,
    weight INTEGER NOT NULL,

    FOREIGN KEY (brand_id) REFERENCES brand(id),
    FOREIGN KEY (color_id) REFERENCES color(id),
    FOREIGN KEY (neckline_id) REFERENCES neckline(id),
    FOREIGN KEY (sleeves_id) REFERENCES sleeves(id),
    FOREIGN KEY (type_id) REFERENCES type(id),
    FOREIGN KEY (condition_id) REFERENCES condition(id),
    FOREIGN KEY (size_id) REFERENCES size(id)
);

CREATE TABLE IF NOT EXISTS note (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    sweater_id INTEGER NOT NULL,
    content TEXT NOT NULL,

    FOREIGN KEY (sweater_id) REFERENCES sweater(id)
        ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS piece (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    sweater_id INTEGER NOT NULL,
    piece_type_id INTEGER NOT NULL,
    original_weight INTEGER NOT NULL,
    current_weight INTEGER NOT NULL,
    continuous INTEGER NOT NULL,

    FOREIGN KEY (sweater_id) REFERENCES sweater(id)
        ON DELETE CASCADE,

    FOREIGN KEY (piece_type_id) REFERENCES piece_type(id)
);
