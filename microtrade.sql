--
-- SQLiteStudio v3.4.17 生成的文件，周四 10月 16 08:51:09 2025
--
-- 所用的文本编码：UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- 表：authorizations
CREATE TABLE IF NOT EXISTS authorizations (
    id         INTEGER,
    created_at DATETIME NOT NULL
                        DEFAULT CURRENT_TIMESTAMP,
    removed_at DATETIME,
    user_id    INTEGER  NOT NULL,
    token      TEXT     NOT NULL,
    PRIMARY KEY (
        id
    )
);


-- 表：cart_items
CREATE TABLE IF NOT EXISTS cart_items (
    id         INTEGER,
    created_at DATETIME NOT NULL
                        DEFAULT CURRENT_TIMESTAMP,
    removed_at DATETIME,
    cart_id    INTEGER  NOT NULL,
    product_id INTEGER  NOT NULL,
    quantity   INTEGER  NOT NULL
                        DEFAULT (0),
    PRIMARY KEY (
        id
    )
);


-- 表：carts
CREATE TABLE IF NOT EXISTS carts (
    id         INTEGER,
    created_at DATETIME NOT NULL
                        DEFAULT CURRENT_TIMESTAMP,
    removed_at DATETIME,
    user_id    INTEGER  NOT NULL,
    PRIMARY KEY (
        id
    )
);


-- 表：logs
CREATE TABLE IF NOT EXISTS logs (
    id         INTEGER,
    created_at DATETIME NOT NULL,
    removed_at DATETIME,
    type       TEXT     NOT NULL,
    text       TEXT     NOT NULL
                        DEFAULT "",
    PRIMARY KEY (
        id
    )
);


-- 表：notifications
CREATE TABLE IF NOT EXISTS notifications (
    id         INTEGER,
    created_at DATETIME NOT NULL
                        DEFAULT CURRENT_TIMESTAMP,
    removed_at DATETIME,
    user_id    INTEGER  NOT NULL,
    text       TEXT     NOT NULL,
    PRIMARY KEY (
        id
    )
);


-- 表：order_items
CREATE TABLE IF NOT EXISTS order_items (
    id         INTEGER,
    created_at DATETIME        NOT NULL
                               DEFAULT CURRENT_TIMESTAMP,
    removed_at DATETIME,
    order_id   INTEGER         NOT NULL,
    product_id INTEGER         NOT NULL,
    quantity   INTEGER         NOT NULL,
    cost       DECIMAL (10, 2) NOT NULL,
    PRIMARY KEY (
        id
    )
);


-- 表：orders
CREATE TABLE IF NOT EXISTS orders (
    id         INTEGER,
    created_at DATETIME        NOT NULL
                               DEFAULT CURRENT_TIMESTAMP,
    removed_at DATETIME,
    user_id    INTEGER         NOT NULL,
    cost       DECIMAL (10, 2) NOT NULL,
    status     TEXT            NOT NULL,
    PRIMARY KEY (
        id
    )
);


-- 表：product_promotion_relations
CREATE TABLE IF NOT EXISTS product_promotion_relations (
    id           INTEGER  PRIMARY KEY,
    created_at   DATETIME NOT NULL,
    removed_at   DATETIME,
    product_id   INTEGER  NOT NULL,
    promotion_id INTEGER  NOT NULL
);


-- 表：products
CREATE TABLE IF NOT EXISTS products (
    id          INTEGER,
    created_at  DATETIME        NOT NULL
                                DEFAULT CURRENT_TIMESTAMP,
    removed_at  DATETIME,
    name        TEXT            NOT NULL,
    description TEXT,
    price       DECIMAL (10, 2) NOT NULL,
    stock       INTEGER         NOT NULL,
    category    TEXT,
    image_url   TEXT,
    PRIMARY KEY (
        id
    )
);


-- 表：promotions
CREATE TABLE IF NOT EXISTS promotions (
    id          INTEGER  PRIMARY KEY,
    created_at  DATETIME NOT NULL,
    removed_at  DATETIME,
    description TEXT,
    start_at    DATETIME NOT NULL,
    end_at      DATETIME NOT NULL,
    strategy    TEXT     NOT NULL,
    threshold   REAL     NOT NULL,
    value       REAL     NOT NULL,
    CHECK (strategy IN ("percentage_discount", "fixed_amount_discount", "null") ) 
);


-- 表：users
CREATE TABLE IF NOT EXISTS users (
    id            INTEGER,
    created_at    DATETIME NOT NULL
                           DEFAULT CURRENT_TIMESTAMP,
    removed_at    DATETIME,
    username      TEXT     NOT NULL
                           UNIQUE,
    password_hash TEXT     NOT NULL,
    avatar_url    TEXT,
    is_admin      BOOLEAN  NOT NULL
                           DEFAULT (0),
    PRIMARY KEY (
        id
    )
);


-- 索引：idx_cart_items_unique_active
CREATE UNIQUE INDEX IF NOT EXISTS idx_cart_items_unique_active ON cart_items (
    cart_id,
    product_id
)
WHERE removed_at IS NULL;


-- 索引：idx_unique_is_admin
CREATE UNIQUE INDEX IF NOT EXISTS idx_unique_is_admin ON users (
    is_admin
)
WHERE is_admin = 1;


COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
