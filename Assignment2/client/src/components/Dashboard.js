import React, { Fragment, useState, useEffect } from "react";
import './Dashboard.css';
import altimg from "./blank.png";

import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faClock, faEye, faAddressBook, faMapMarkerAlt, faCalendarAlt, faLink, faCoins, faArrowAltCircleUp, faArrowAltCircleDown, faSignOutAlt } from '@fortawesome/fontawesome-free-solid';
import { faHome, faSearch, faTags, faList } from '@fortawesome/free-solid-svg-icons';

const parsehtml = require("html-react-parser");

const Dashboard = ({setAuth}) => {

    const [name, setName] = useState("");
    const [reputation, setReputation] = useState("");
    const [views, setViews] = useState("");
    const [upvotes, setups] = useState("");
    const [downvotes, setdowns] = useState("");
    const [location, setlocation] = useState("");
    const [website_url, setweburl] = useState("");
    const [profile_url, setdp] = useState("");
    const [about_me, setbio] = useState("");
    const [creation_date, setjoined] = useState("");
    const [last_access_date, setlastseen] = useState("");

    async function getName()
    {
        try {
            const response = await fetch("http://localhost:5000/dashboard/", {
                method: "GET",
                headers: {token: localStorage.token}
            });

            const parseRes = await response.json();
            setName(parseRes.display_name);
            setReputation(parseRes.reputation);
            setViews(parseRes.views);
            setbio(parseRes.about_me);
            setups(parseRes.up_votes);
            setdowns(parseRes.down_votes);
            setlocation(parseRes.location);
            setweburl(parseRes.website_url);
            setdp(parseRes.profile_image_url);
            setjoined(parseRes.creation_date);
            setlastseen(parseRes.last_access_date);
        }
        catch (err)
        {
            console.error(err.message);           
        }
    }

    const logout = (e) => {
        e.preventDefault()
        localStorage.removeItem("token");
        setAuth(false);
    }

    useEffect(()=> {
        getName();
    }, []);

    return (
        <Fragment>

        <div><h1 style={{ color: "rgb(185, 90, 42)"}}>Hello, {name}!</h1></div> 
        
        <div className="first"> <h5> <FontAwesomeIcon icon = {faCalendarAlt}/> Joined Community on</h5>
                <p style={{color: "black"}}>{creation_date}</p> </div>
        
        <div className="second">
            <h5><FontAwesomeIcon icon={faClock} />&nbsp; Last Seen</h5>
            <p style={{color: "black"}}>{last_access_date}</p>       
        </div>

         <div className="mid">
          <h5><FontAwesomeIcon icon={faMapMarkerAlt} />
          &nbsp; Location</h5>
                <p style={{color: "black"}}>{location}</p> 
         </div>

        {profile_url ? <img src = {profile_url} alt = "Cannot Load DP" /> : <img src = {altimg}/>}
           
        <div className="middlebox"> 
            <h5> <FontAwesomeIcon icon={faAddressBook} /> &ensp; Bio</h5>
            <div style={{color: "black"}}> {about_me ? parsehtml(about_me) : ''} </div>
            <h5>  <FontAwesomeIcon icon={faLink} /> &ensp; Web URL</h5>
            <p style={{color: "black"}}>{website_url}</p>
        </div> 

        <div className="grid-container">
        <div className="grid-item"> <h4> <FontAwesomeIcon icon={faCoins} /> &nbsp; Reputation </h4> <p> {reputation} </p> </div>
        <div className="grid-item"> <h4> <FontAwesomeIcon icon={faEye} /> &nbsp; Views </h4> <p> {views}  </p> </div>
        <div className="grid-item"> <h4> <FontAwesomeIcon icon={faArrowAltCircleUp} /> &nbsp;  Upvotes </h4> <p> {upvotes} </p>  </div>  
        <div className="grid-item"> <h4> <FontAwesomeIcon icon={faArrowAltCircleDown} /> &nbsp;  Downvotes</h4> <p>{downvotes}</p> </div>
        </div>

        <header className="nav-header" role="banner">
            <h1 className="nav-logo">
                <a href="#">stack <span>overflow</span></a>
            </h1>
            <div className="nav-wrap">
                <nav className="main-nav" role="navigation">
                <ul className="unstyled list-hover-slide">
                <li> <a href = "http://localhost:3000/dashboard/"> <FontAwesomeIcon icon={faHome} /> Home</a></li>
                    <li><a href="http://localhost:3000/posts/"><FontAwesomeIcon icon={faList} /> Show Posts</a></li>
                    <li><a href="http://localhost:3000/stalk/"><FontAwesomeIcon icon={faSearch} /> Find People</a></li>
                    <li><a href="http://localhost:3000/search/"><FontAwesomeIcon icon={faTags} /> Search by Tag</a></li>
                    <li><a href="http://localhost:3000/login/"> <button className="btn btn-primary" onClick={e => logout(e)} ><FontAwesomeIcon icon={faSignOutAlt}/>Logout</button></a></li>
                </ul>
                </nav>
                <ul className="social-links list-inline unstyled list-hover-slide">
                <li><a href="https://twitter.com/StackOverflow?ref_src=twsrc%5Egoogle%7Ctwcamp%5Eserp%7Ctwgr%5Eauthor">Twitter</a></li>
                <li><a href="https://www.instagram.com/thestackoverflow/?hl=en">Instagram</a></li>
                <li><a href="https://www.facebook.com/officialstackoverflow/">Facebook</a></li>
                <li><a href="https://www.linkedin.com/company/stack-overflow">Linked in</a></li>
                </ul>
            </div>
        </header>

       </Fragment> 
    );
};

export default Dashboard;