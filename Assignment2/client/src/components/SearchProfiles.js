import React, { Fragment, useEffect, useState } from "react";
import { useNavigate } from "react-router-dom"; 
import altimg from "./blank.png";
import './SearchProfiles.css';

import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faHome, faSearch, faTags, faList, faSignOutAlt } from '@fortawesome/free-solid-svg-icons';


function SearchProfiles({setAuth}) {
  const navigate = useNavigate();
  const [searchQuery, setSearchQuery] = useState("");
  const [searchResults, setSearchResults] = useState([]);

  const handleSearchInput = (e) => {
    const query = e.target.value;
    setSearchQuery(query);
  };

  const logout = (e) => {
    e.preventDefault()
    localStorage.removeItem("token");
    setAuth(false);
    navigate(`/login`);
}

  const fetchSearchResults = async (query) => {
    const response = await fetch("http://localhost:5000/stalk", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        token: localStorage.token,
      },
      body: JSON.stringify({ search_name: query }),
    });

    if (response.status === 200) {
      const data = await response.json();
      setSearchResults(data);
    } else {
      console.log("Failed to fetch that profile");
    }
  };

  useEffect(() => {
    if (searchQuery.length >= 1) {
      fetchSearchResults(searchQuery);
    } else {
      setSearchResults([]);
    }
  }, [searchQuery]);

  const handleClick = (e, profile_id) => {
    e.preventDefault()
    navigate(`/view/${profile_id}`);
  }

  return (
    <Fragment>
      <input
        type="search"
        value={searchQuery}
        onChange={handleSearchInput}
        placeholder="Search for people here"
        className="form-control my-3"
      />
      <div className="card-grid">
        {searchResults.map((profile, index) => (
          <div className="card" key={index}>
            {profile.profile_image_url ? (
              <img className="card-img-top" src={profile.profile_image_url} alt={profile.display_name} />
            ) : (
              <img className="card-img-top" src={altimg} alt={profile.display_name} />
            )}
            <div className="card-body">
              <h5 className="card-title">{profile.display_name}</h5>
              <button className="btn btn-primary" onClick={e => handleClick(e, profile.id)}>View Profile</button>
            </div>
          </div>
        ))}
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

export default SearchProfiles;