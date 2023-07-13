const express = require("express");
const router = express.Router();
const pool = require("../db");
const authorization = require("../middleware/authorization");

router.post("/", authorization, async(req, res) => {
    try {
        const {postid, title, body} = req.body;
        const post_list = await pool.query(`SELECT * FROM EDITPOST($1, $2, $3)`, [postid, title, body]);
        res.header("Content-Type", "application/json");
        res.json(post_list.rows)
    } catch (err) {
        console.error(err.message);
    }
})

module.exports = router;