const jwt = require("jsonwebtoken");
require("dotenv").config();

module.exports = function(req, res, next){
    try {
        
        const jwtToken = req.header("token");

        if(!jwtToken)
        {
            // console.log("here1");
            return res.status(403).json({msg: "authorization denied"})
        }

        const verify = jwt.verify(jwtToken, process.env.jwtSecret);
        req.user = verify.user;

        next();
    } catch (err) {
        console.error(err.message);
        return res.status(403).json("Not Authorize")
    }
}