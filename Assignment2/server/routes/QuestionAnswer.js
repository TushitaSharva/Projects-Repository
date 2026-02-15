const express = require("express");
const router = express.Router();
const pool = require("../db");
const authorization = require("../middleware/authorization");

// For displaying posts
router.get("/", authorization, async(req, res) => {
    try {
        const { postid } = req.query;
        const profile = await pool.query(`select * from posts where parent_id = $1 UNION select * from posts where id = $2 order by creation_date asc;`, [postid, postid])
        res.header("Content-Type", "application/json");
        res.json(profile.rows)
    } catch (err) {
        console.error(err.message);
    }
})

module.exports = router;