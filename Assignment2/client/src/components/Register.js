import React, { Fragment, useState } from "react";
import {Link} from "react-router-dom";
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faUser, faLock, faMapMarkerAlt, faImage, faLink, faGlobe } from '@fortawesome/free-solid-svg-icons';
import './Register.css';

const Register = ({setAuth}) => {

    const [inputs, setInputs] = useState({
        name: "",
        password: "",
        location: "",
        profile_image_url: "",
        website_url: "",
        about_me: ""
    })

    const onChange = async (e) => {
        setInputs({...inputs, [e.target.name] : e.target.value})
    }

    const onSubmit = async (e) => {
        e.preventDefault();

        if(inputs.name == "" || inputs.password == "")
        {
            return;
        }

        const body = {name: inputs.name, password: inputs.password, location: inputs.location, profile_image_url: inputs.profile_image_url, website_url: inputs.website_url, about_me: inputs.about_me};

        try {
            const response = await fetch("http://localhost:5000/auth/register", {
            method: "POST",
            headers: {"Content-Type" : "application/json"},
            body: JSON.stringify(body)
        })
            const parseRes = await response.json();

            localStorage.setItem("token", parseRes.token);
            setAuth(true);
        } catch (err) {
            console.error(err.message)
        }
    }

    return (
        <div className="reg-container">
          <h1 className="text-center my-5">REGISTER</h1>
          <form onSubmit={onSubmit}>
            <div className="input-container">
              <span className="icon"><FontAwesomeIcon icon={faUser} /> Display Name</span>
              <input type="text" name="name" className="form-control my-3" value={inputs.name} onChange={onChange}/>
            </div>
            <div className="input-container">
              <span className="icon"><FontAwesomeIcon icon={faLock} /> Password</span>
              <input type="password" name="password" className="form-control my-3" value={inputs.password} onChange={onChange}/>
            </div>
            <div className="input-container">
              <span className="icon"><FontAwesomeIcon icon={faMapMarkerAlt} /> Location</span>
              <input type="text" name="location" className="form-control my-3" value={inputs.location} onChange={onChange}/>
            </div>
            <div className="input-container">
              <span className="icon"><FontAwesomeIcon icon={faImage} /> Profile Image URL</span>
              <input type="text" name="profile_image_url"  className="form-control my-3" value={inputs.profile_image_url} onChange={onChange}/>
            </div>
            <div className="input-container">
              <span className="icon"><FontAwesomeIcon icon={faLink} /> Website URL</span>
              <input type="text" name="website_url" className="form-control my-3" value={inputs.website_url} onChange={onChange}/>
            </div>
            <div className="input-container">
            <span className="icon"><FontAwesomeIcon icon={faGlobe} /> Bio</span>
              <textarea type="text" name="about_me" className="form-control my-3" value={inputs.about_me} onChange={onChange}/>
            </div>
            <button type="submit" className="reg-btn reg-btn-success reg-btn-block">Submit</button>
          </form>
          <Link to="/login" className="login-link">Login</Link>
        </div>
      );
};

export default Register;