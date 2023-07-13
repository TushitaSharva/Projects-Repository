const express = require("express");
const router = express.Router();
const pool = require("../db");
const jwtGenerator = require("../utils/jwtGenerator");
const validInfo = require("../middleware/validInfo");
const authorization = require("../middleware/authorization");

// Registering
router.post("/register", validInfo, async (req, res) => {
  try {
    // 1. Destructure the req.body (name, password)
    const { name, password, location, profile_image_url, website_url, about_me } = req.body;
    
    // 2. Check if the user exists (if yes, throw error)
    const status = await pool.query("SELECT * FROM auth_verify($1, $2)", [
      name,
      password,
    ]);
    // console.log(res.rows[0]);

    // console.log(status.rows[0].auth_verify);
    if (status.rows[0].auth_verify !== 0) {
      // This means a user already exists with this name
      return res.status(401).send("User already exists");
    } else {
      // 3. Bcrypt the user password
      // 4. Enter the new user into the database

        const new_user = await pool.query(`INSERT INTO users(id, account_id, reputation, display_name, pwd, location, profile_image_url, website_url, about_me, creation_date) VALUES ((SELECT * FROM assign_user_id()), (SELECT * FROM assign_user_id()),1, $1, $2, $3, $4, $5, $6, NOW()) RETURNING *`, [name, password, location, profile_image_url, website_url, about_me]);
        console.log(new_user.rows[0].id);
        // 5. Generating our jwt token
        const token = jwtGenerator(new_user.rows[0].id);
        // console.log(token);
        res.json({ token });
    }
  } catch (err) {
    console.log(err.message);
    res.status(500).send("Server Error");
  }
});

// Login route
router.post("/login", validInfo, async (req, res) => {
  // 1. Destructure req.body
  const { name, password } = req.body;

  // 2. User doesn't exist (if not then we throw error)
  const status = await pool.query("SELECT * FROM auth_verify($1, $2)", [
    name,
    password,
  ]);

  console.log(status.rows[0].auth_verify);

  if (status.rows[0].auth_verify === 0) {
    // Means the username doesn't exist
    return res.status(401).json("Invalid Credential");
  }
  // 3. Check if incoming password is the same as database password
  else if (status.rows[0].auth_verify === 1) {
    return res.status(401).json("Invalid Credential");
  }
  // 4. Give them the jwt token
  const user = await pool.query("SELECT * FROM users WHERE display_name = $1", [
    name,
  ]);
  const token = jwtGenerator(user.rows[0].id);
  res.json({ token });
});

router.get("/is-verify", authorization, async (req, res) => {
  try {
    res.json(true);
  } catch (err) {
    console.error(err.message);
    res.status(500).sendStatus("Server Error");
  }
});

module.exports = router;
