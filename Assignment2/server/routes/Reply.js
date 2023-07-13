const express = require("express");
const router = express.Router();
const pool = require("../db");
const authorization = require("../middleware/authorization");

router.post("/", authorization, async (req, res) => {
  try {
    const { owner_id, owner_name, parent_postid, title, tags, body } = req.body;

    const post_list = await pool.query(
      `SELECT * FROM replyPost($1, $2, $3, $4, $5, $6)`,
      [owner_id, owner_name, parent_postid, title, tags, body]
    );
    res.header("Content-Type", "application/json");
    res.json(post_list.rows);
  } catch (err) {
    console.error(err.message);
  }
});

module.exports = router;
