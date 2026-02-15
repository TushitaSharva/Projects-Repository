import React, { Fragment, useState, useEffect } from 'react';
import './App.css';
import { BrowserRouter as Router, Routes, Route, Navigate } from 'react-router-dom';

// components
import Dashboard from './components/Dashboard';
import Login from './components/Login';
import Register from './components/Register';
import DisplayPosts from './components/DisplayPosts';
import SearchProfiles from './components/SearchProfiles';
import OtherProfile from './components/OtherProfile';
import QuestionAnswer from './components/QuestionAnswer';
import SearchPosts from './components/SearchPosts';
import PostEditor from './components/PostEditor';
import Reply from './components/Reply';
import Create from './components/Create';

function App() {
  const [isAuthenticated, setIsAuthenticated] = useState(false);

  const setAuth = (boolean) => {
    setIsAuthenticated(boolean);
  };

  async function isAuth() {
    try {
      const response = await fetch('http://localhost:5000/auth/is-verify', {
        method: 'GET',
        headers: { token: localStorage.token },
      });

      const parseRes = await response.json();

      parseRes === true ? setIsAuthenticated(true) : setIsAuthenticated(false);
    } catch (err) {
      console.error(err.message);
    }
  }

  useEffect(() => {
    isAuth();
  }, []);

  return (
    <Fragment>
      <Router>
        <div className="container">
          <Routes>
            <Route exact path="/login" element={!isAuthenticated ? <Login setAuth={setAuth} /> : <Navigate to="/dashboard" />}/>
            <Route exact path="/register" element={!isAuthenticated ? (<Register setAuth={setAuth} />) : (<Navigate to="/login" />)}/>
            <Route exact path="/dashboard" element={isAuthenticated ? (<Dashboard setAuth={setAuth} />) : (<Navigate to="/login" />)}/>
            <Route exact path="/posts" element= {<DisplayPosts setAuth={setAuth}/>}/>
            <Route path="/stalk" element= {<SearchProfiles setAuth={setAuth}/>}/>
            <Route exact path = "/view/:id" element = {<OtherProfile setAuth={setAuth}/>}/>
            <Route exact path = "/question/:postid" element = {<QuestionAnswer />}/>
            <Route exact path = "/search" element = {<SearchPosts setAuth={setAuth}/>}/>
            <Route exact path = "/editPost/:id" element = {<PostEditor />}/>
            <Route exact path = "/replyPost/:id" element = {<Reply />}/>
            <Route exact path = "/create" element = {<Create />}/>
            
          </Routes>
        </div>
      </Router>
    </Fragment>
  );
}

export default App;