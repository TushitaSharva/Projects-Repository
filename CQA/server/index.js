const express = require("express");
const app = express()
const cors = require("cors");
const bodyParser = require("body-parser");

// Middleware
app.use(express.json());
app.use(bodyParser.json());
app.use(cors());

// ROUTES//

// Register and login routes
app.use("/auth", require("./routes/Auth"));

// Dashboard Routes
app.use("/dashboard", require("./routes/dashboard"))
app.use("/posts", require("./routes/DisplayPosts"))
app.use("/stalk", require("./routes/SearchProfiles"))
app.use("/view", require("./routes/OtherProfile"))
app.use("/question", require("./routes/QuestionAnswer"))
app.use("/filterposts", require("./routes/SearchPosts"))
app.use("/editPost", require("./routes/PostEditor"))
app.use("/reply", require("./routes/Reply"))
app.use("/create", require("./routes/Create"))
app.use("/delete", require("./routes/Delete"))
app.use("/vote", require("./routes/Vote"))

app.listen(5000, () =>
{
    console.log("Server is running on port 5000");
});