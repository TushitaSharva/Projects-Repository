const express = require("express");
const router = express.Router();
const pool = require("../db");
const authorization = require("../middleware/authorization");

// For displaying posts
router.get("/", authorization, async(req, res) => {
    try {
        const posts = await pool.query("SELECT * FROM posts WHERE owner_user_id = $1", [req.user.id])
        res.header("Content-Type", "application/json");
        res.json(posts.rows)
    } catch (err) {
        console.error(err.message);
    }
})

module.exports = router;