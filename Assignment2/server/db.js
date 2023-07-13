const { Pool } = require("pg");

const pool = new Pool({
    user: "tushita",
    password: "1234",
    host: "localhost",
    port: 5432,
    database: "cqadb"
});

module.exports = pool;