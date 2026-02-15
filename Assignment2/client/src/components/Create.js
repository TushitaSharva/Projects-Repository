import React, { Fragment, useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";
const parsehtml = require("html-react-parser");

function Create() {
  const initialValues = {
    title: "",
    tags: "",
    body: "",
  };

  const [values, setValues] = useState(initialValues);

  const { title, tags, body } = values;

  const onBodyChange = (e) => {
    const newValue =
      e.target.name === "body" ? parsehtml(e.target.value) : e.target.value;
    setValues({ ...values, [e.target.name]: newValue });
  };

  const navigate = useNavigate();

  const onSubmit = async (e) => {
    e.preventDefault();
    try {
      const response = await fetch("http://localhost:5000/dashboard/", {
        method: "GET",
        headers: { token: localStorage.token },
      });

      const parseRes = await response.json();
      const body = {
        owner_id: parseRes.id,
        owner_name: parseRes.display_name,
        title: values.title,
        tags: values.tags,
        body: values.body,
      };
      console.log(body);

      console.log("Before second fetch request");

      const response2 = await fetch(`http://localhost:5000/create`, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
          token: localStorage.token,
        },
        body: JSON.stringify(body),
      });

      // console.log("Here it came");

      await response2.json();
      // console.log("Here it came");
      navigate(`/posts`);
    } catch (err) {
      console.error(err.message);
    }
  };

  return (
    <Fragment>
      <input
        className="form-control my-3"
        name="title"
        type="text"
        value={values.title}
        onChange={(e) => {
          setValues({ ...values, [e.target.name]: e.target.value });
        }}
        placeholder="title"
      />
      <input
        className="form-control my-3"
        name="tags"
        type="text"
        value={values.tags}
        onChange={(e) => {
          setValues({ ...values, [e.target.name]: e.target.value });
        }}
        placeholder="tags"
      />
      <textarea
        className="form-control my-3"
        name="body"
        value={values.body}
        onChange={onBodyChange}
        placeholder="body"
      />
      <button className="btn btn-primary" onClick={onSubmit}>
        Post
      </button>
    </Fragment>
  );
}

export default Create;
