const express = require("express");
const router = express.Router();
const pool = require("../db");
const authorization = require("../middleware/authorization");

// For displaying posts
router.post("/", authorization, async(req, res) => {
    try {
        const {search_name} = req.body;
        const profile_list = await pool.query(`SELECT * FROM suggestProfiles($1)`, [search_name])
        res.header("Content-Type", "application/json");
        res.json(profile_list.rows)
    } catch (err) {
        console.error(err.message);
    }
})

module.exports = router;