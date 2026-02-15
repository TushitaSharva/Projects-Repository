import React, { Fragment, useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";
import { useParams } from "react-router-dom";
const parsehtml = require("html-react-parser");

function Reply() {
  const initialValues = {
    title: "",
    tags: "",
    body: "",
  };

  const pid = useParams();
  const [values, setValues] = useState(initialValues);
  const [name, setName] = useState("");
  const [id, setId] = useState("");

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
      setName(parseRes.display_name);
      setId(parseRes.id);
      const body = { owner_id: id, owner_name: name, parent_postid: pid.id, title: values.title, tags: values.tags, body: values.body };
      console.log(body);

      const response2 = await fetch(
        `http://localhost:5000/reply?postid=${pid.id}`,
        {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
            token: localStorage.token,
          },
          body: JSON.stringify(body),
        }
      );

      await response2.json();
      navigate(`/question/${pid.id}`);
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

export default Reply;
