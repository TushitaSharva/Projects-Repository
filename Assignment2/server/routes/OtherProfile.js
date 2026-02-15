const express = require("express");
const router = express.Router();
const pool = require("../db");
const authorization = require("../middleware/authorization");

// For displaying posts
router.post("/", authorization, async(req, res) => {
    try {
        const { id } = req.query;
        const profile = await pool.query(`SELECT * FROM users where id = $1`, [id])
        res.header("Content-Type", "application/json");
        res.json(profile.rows[0])
        console.log(profile.rows[0]);
    } catch (err) {
        console.error(err.message);
    }
})

module.exports = router;