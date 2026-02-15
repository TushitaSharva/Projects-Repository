import React, { Fragment, useState, useEffect } from "react";
import { useParams } from "react-router-dom";
import { useNavigate } from "react-router-dom";
import altimg from "./blank.png";
import './OtherProfile.css';

import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faClock, faEye, faAddressBook, faMapMarkerAlt, faCalendarAlt, faLink, faCoins, faArrowAltCircleUp, faArrowAltCircleDown, faSignOutAlt } from '@fortawesome/fontawesome-free-solid';
import { faHome, faSearch, faTags, faList } from '@fortawesome/free-solid-svg-icons';


const parsehtml = require("html-react-parser");

export default function OtherProfile({setAuth}) {
    const [profile, setProfile] = useState({});
    const sid = useParams();

    const navigate = useNavigate();
    const logout = (e) => {
        e.preventDefault()
        localStorage.removeItem("token");
        setAuth(false);
        navigate(`/login`);
    }

    async function otherProfile() {
        const response = await fetch(`http://localhost:5000/view?id=${sid.id}`, {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
                token: localStorage.token,
            },
        });

        if(response.status === 200)
        {
          const data = await response.json();
          setProfile(data);
        }
        else
        {
          console.log("Failed to fetch their profile");
        }
    }

    useEffect(() => {
        otherProfile();
      }, []);

    return (
        <Fragment>
            <h1 style={{color: "rgb(185, 90, 42)"}}>{profile.display_name}'s Dashboard</h1>

                <div className="first"> <h5> <FontAwesomeIcon icon = {faCalendarAlt}/> Joined Community on</h5>
                <p style={{color: "black"}}> {profile.creation_date}</p> </div>
        
        <div className="second">
            <h5>   <FontAwesomeIcon icon={faClock} />
                &nbsp; Last Seen</h5>
                <p style={{color: "black"}}>{profile.last_access_date}</p>       
         </div> 

         <div className="mid">
          <h5><FontAwesomeIcon icon={faMapMarkerAlt} />
          &nbsp; Location</h5>
                <p style={{color: "black"}}>{profile.location}</p> 
         </div>

             {profile.profile_image_url ? <img src = {profile.profile_image_url} alt = "Cannot Load DP" /> : <img src = {altimg}/>}
           
            <div className="middlebox">
        
        <h5> <FontAwesomeIcon icon={faAddressBook} />
        &ensp; Bio</h5>
        <div style={{color: "black"}}>{profile.about_me ? parsehtml(profile.about_me) : ''} </div>
        <h5>  <FontAwesomeIcon icon={faLink} />
        &ensp; Web URL</h5>
        <p style={{color: "black"}}>{profile.website_url}</p>
        </div> 

<div className="grid-container">
  <div className="grid-item"> <h4> <FontAwesomeIcon icon={faCoins} /> &nbsp; Reputation </h4> <p> {profile.reputation} </p> </div>
  <div className="grid-item"> <h4> <FontAwesomeIcon icon={faEye} /> &nbsp; Views </h4> <p> {profile.views}  </p> </div>
  <div className="grid-item"> <h4> <FontAwesomeIcon icon={faArrowAltCircleUp} /> &nbsp;  Upvotes </h4> <p> {profile.up_votes} </p>  </div>  
  <div className="grid-item"> <h4> <FontAwesomeIcon icon={faArrowAltCircleDown} /> &nbsp;  Downvotes</h4> <p>{profile.down_votes}</p> </div>
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
}