import React, { Fragment, useEffect, useState } from "react";
import { useNavigate, useParams } from "react-router-dom";

import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faHome, faSearch, faTags, faList, faSignOutAlt } from '@fortawesome/free-solid-svg-icons';

const parsehtml = require("html-react-parser");
// import './SearchPosts.css';


function SearchPosts({setAuth}) {
  const navigate = useNavigate();
  const initialValues = {
    tag1: "",
    tag2: "",
    tag3: "",
    tag4: "",
    tag5: "",
    owner: "",
    sortby: "",
  };

  const [values, setValues] = useState(initialValues);
  const [results, setResults] = useState([]);
  const pid = useParams();

  const {tag1, tag2, tag3, tag4, tag5, owner, sortby} = values;

  const logout = (e) => {
    e.preventDefault()
    localStorage.removeItem("token");
    setAuth(false);
    navigate(`/login`);
  }

  const onChange = (e) => {
    setValues({...values, [e.target.name]: e.target.value});
  }

  const onSubmit = async(e) => {
    e.preventDefault()
    try {
      const body = {tag1: values.tag1, tag2: values.tag2, tag3: values.tag3, tag4: values.tag4, tag5: values.tag5, owner: values.owner, sortby: values.sortby};

      const response = await fetch("http://localhost:5000/filterposts", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
          token: localStorage.token,
        },
        body: JSON.stringify(body)
      });

      const data = await response.json();
      setResults(data);
    } catch (err) {
      console.error(err.message);
    }
  }

  const handleViewClick = (e, postid) => {
    e.preventDefault()
    console.log(postid);
    navigate(`/question/${postid}`)
  }

  return (
    <Fragment>
      <input className="form-control my-3" name="tag1" type="text" value = {values.tag1} onChange={onChange} placeholder="filter by tag"/>
      <input className="form-control my-3" name="tag2" type="text" value = {values.tag2} onChange={onChange} placeholder="filter by tag"/>
      <input className="form-control my-3" name="tag3" type="text" value = {values.tag3} onChange={onChange} placeholder="filter by tag"/>
      <input className="form-control my-3" name="tag4" type="text" value = {values.tag4} onChange={onChange} placeholder="filter by tag"/>
      <input className="form-control my-3" name="tag5" type="text" value = {values.tag5} onChange={onChange} placeholder="filter by tag"/>
      <input className="form-control my-3" name="owner" type="text" value = {values.owner} onChange={onChange} placeholder="filter by owner"/>
      <input className="form-control my-3" name="sortby" type="text" value = {values.sortby} onChange={onChange} placeholder="creation_date or score"/>
      <button className="btn btn-primary" onClick={onSubmit}>Filter</button>
      <ul>
          {results.map((post) => (
            <li key={post.id} style={{ border: "1px solid white", padding: "10px", overflow: "hidden"}}>
              <h5>
                {post.title} - {post.owner}
                <button className="spro-btn spro-btn-primary" onClick={(e) => handleViewClick(e, post.id)}>View</button>
              </h5>
              <div
                dangerouslySetInnerHTML={{
                  __html: post.body.replace(
                    /<code>(.*?)<\/code>/gs,
                    '<span class="code">$1</span>'
                  ),
                }}
              ></div>
              <style>{`
                .code {
                  padding: 10px;
                  border-radius: 5px;
                  color: lightblue;
                  overflow-x: hidden;
                }
              `}</style>
            </li>
          ))}
        </ul>
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
  )
}

export default SearchPosts;