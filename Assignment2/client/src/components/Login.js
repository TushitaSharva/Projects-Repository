import React, { Fragment, useState } from "react";
import { Link } from "react-router-dom";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faUser, faLock } from "@fortawesome/free-solid-svg-icons";
import "./Login.css";

const Login = ({ setAuth }) => {
  const [inputs, setInputs] = useState({
    name: "",
    password: "",
  });

  const { name, password } = inputs;

  const onChange = (e) => {
    setInputs({ ...inputs, [e.target.name]: e.target.value });
  };

  const onSubmit = async (e) => {
    e.preventDefault();
    try {
      if (inputs.name == "" || inputs.password == "") {
        return;
      }

      const body = { name: inputs.name, password: inputs.password };

      const response = await fetch("http://localhost:5000/auth/login", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(body),
      });

      if (response.status != 200) {
        return;
      } else {
        const parseRes = await response.json();
        localStorage.setItem("token", parseRes.token);
        setAuth(true);
      }
    } catch (err) {
      console.error(err.message);
    }
  };
  return (
    <Fragment>
      <div className="login-container">
        <h1 className="text-center my-3">LOGIN</h1>
        <form onSubmit={onSubmit}>
          <div className="form-group">
            <label htmlFor="name">
              <FontAwesomeIcon icon={faUser} /> Display Name
            </label>
            <input
              type="text"
              name="name"
              id="name"
              className="form-control"
              value={inputs.name}
              onChange={onChange}
            />
          </div>
          <div className="form-group">
            <label htmlFor="password">
              <FontAwesomeIcon icon={faLock} /> Password
            </label>
            <input
              type="password"
              name="password"
              id="password"
              className="form-control"
              value={inputs.password}
              onChange={onChange}
            />
          </div>
          <button className="login-btn login-btn-success login-btn-block">
            Submit
          </button>
        </form>
        <Link to="/register" className="reg-link">
          No account? Register
        </Link>
      </div>
    </Fragment>
  );
};

export default Login;
