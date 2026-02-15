import React, { Fragment, useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";
import { confirmAlert } from 'react-confirm-alert';

import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faEdit, faEye, faPlusCircle, faTrash} from '@fortawesome/fontawesome-free-solid';
import { faHome, faSearch, faTags, faList, faSignOutAlt } from '@fortawesome/free-solid-svg-icons';


const parsehtml = require("html-react-parser");

const DisplayPosts = ({setAuth}) => {
  const [posts, setPosts] = useState([]);

  async function displayPosts() {
    const response = await fetch("http://localhost:5000/posts", {
      method: "GET",
      headers: {
        "Content-Type": "application/json",
        token: localStorage.token,
      },
    });

    if(response.status === 200)
    {
      const data = await response.json();
      setPosts(data);
    }
    else
    {
      console.log("Failed to fetch posts");
    }
  }

  const navigate = useNavigate();

  const logout = (e) => {
    e.preventDefault()
    localStorage.removeItem("token");
    setAuth(false);
    navigate(`/login`);
  }

  useEffect(() => {
    displayPosts();
  }, []); // call the displayPosts function when the component mounts

  
  const handleViewClick = (e, postid) => {
    e.preventDefault()
    navigate(`/question/${postid}`)
  }
  const handleEditClick = (e, postid) => {
    e.preventDefault()
    navigate(`/editPost/${postid}`)
  }
  const handleCreateClick = (e) => {
    e.preventDefault()
    navigate(`/create`)
  }
  const handlleDeleteClick = async (e, postid) => {
    e.preventDefault()
    const response = await fetch(`http://localhost:5000/delete/${postid}`, {
      method: "DELETE",
      headers: {
        "Content-Type": "application/json",
        token: localStorage.token,
      },
    });

    if (response.status !== 200) {
      console.log("Failed to delete post");
    }
    navigate(`/dashboard`)
  }
const submit = (e, postid) => {
  confirmAlert({
    title: 'Confirmation message',
    message: 'Are you sure to delete this post?',
    buttons: [
      {
        label: 'Yes',
        onClick: e => handlleDeleteClick(e, postid)
      },
      {
        label: 'No',
      }
    ]
  });
}
  return (
    <Fragment>
      <h1 style={{color: "white"}}>Your Posts <button className="btn btn-primary" onClick={handleCreateClick}> <FontAwesomeIcon icon={faPlusCircle} /> Create</button> </h1>
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
        
      {posts.length ? (
        <ul>
          {posts.map((post) => (
            <li key={post.id} style={{border: "1px solid white", padding: "10px"}}>
              <> <h5>Q: {post.title} </h5> 
              <button className="btn btn-primary" onClick={e => handleViewClick(e, post.id)}> <FontAwesomeIcon icon={faEye} /> View</button> &nbsp;
              <button className="btn btn-primary" onClick={e => handleEditClick(e, post.id)}> <FontAwesomeIcon icon={faEdit}/> Edit</button> &nbsp;
              
              <button className="btn btn-primary" onClick= {e => handlleDeleteClick(e, post.id)} > <FontAwesomeIcon icon = {faTrash} /> Delete</button></>
              

              <h5>Answer: </h5> {parsehtml(post.body)}
            </li>
          ))}
        </ul>
        
      ) : (
        <p>No posts yet!</p>
        )}
        
        {/* Should make changes here to navigate to post creating interface*/}
    </Fragment>
  );
}

export default DisplayPosts;