const express = require("express");
const router = express.Router();
const pool = require("../db");
const authorization = require("../middleware/authorization");

router.post("/", authorization, async (req, res) => {
  try {
    const { tag1, tag2, tag3, tag4, tag5, owner, sortby } = req.body;

    if (sortby == "creation_date") {
      const post_list = await pool.query(
        `
    SELECT * 
    FROM posts 
    WHERE 
        tags LIKE concat('%', $1::text, '%') AND 
        tags LIKE concat('%', $2::text, '%') AND 
        tags LIKE concat('%', $3::text, '%') AND 
        tags LIKE concat('%', $4::text, '%') AND 
        tags LIKE concat('%', $5::text, '%') AND 
        owner_name LIKE concat('%', $6::text, '%') ORDER BY creation_date ASC
`,
        [tag1, tag2, tag3, tag4, tag5, owner]
      );
      res.header("Content-Type", "application/json");
      res.json(post_list.rows);
    } else if (sortby == "score") {
      const post_list = await pool.query(
        `
    SELECT * 
    FROM posts 
    WHERE 
        tags LIKE concat('%', $1::text, '%') AND 
        tags LIKE concat('%', $2::text, '%') AND 
        tags LIKE concat('%', $3::text, '%') AND 
        tags LIKE concat('%', $4::text, '%') AND 
        tags LIKE concat('%', $5::text, '%') AND 
        owner_name LIKE concat('%', $6::text, '%') ORDER BY score ASC
`,
        [tag1, tag2, tag3, tag4, tag5, owner]
      );
      res.header("Content-Type", "application/json");
      res.json(post_list.rows);
    }

    else
    {
        return;
    }
  } catch (err) {
    console.error(err.message);
  }
});

module.exports = router;
