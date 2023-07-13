const express = require("express");
const router = express.Router();
const pool = require("../db");
const authorization = require("../middleware/authorization");

router.delete("/:id", authorization, async(req, res) => {
    try {
        const {id} = req.params;
        console.log(req.params)
        const post_list = await pool.query(`DELETE FROM posts WHERE id = $1`, [id]);
        res.header("Content-Type", "application/json");
        res.sendStatus(200);
    } catch (err) {
        console.error(err.message);
        res.sendStatus(500);
    }
})

module.exports = router;