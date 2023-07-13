const express = require("express");
const router = express.Router();
const pool = require("../db");
const authorization = require("../middleware/authorization");

router.post("/", authorization, async (req, res) => {
  try {
    const {post_id, owner_id, action} = req.body;
    const status = await pool.query(`SELECT * FROM vote($1, $2, $3)`, [post_id, owner_id, action]);
    res.header("Content-Type", "application/json");
    res.json(status.rows);
  } catch (err) {
    console.error(err.message);
  }
});

module.exports = router;
