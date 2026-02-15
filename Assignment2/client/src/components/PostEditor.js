import React, { Fragment, useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";
import { useParams } from "react-router-dom";
const parsehtml = require("html-react-parser");

function PostEditor() {
  const initialValues = {
    title: "",
    body: "",
  };

  const pid = useParams();
  const [values, setValues] = useState(initialValues);

  const {title, body} = values;

  const onBodyChange = (e) => {
    const newValue = e.target.name === "body" ? parsehtml(e.target.value) : e.target.value;
    setValues({...values, [e.target.name]: newValue});
  }

  const navigate = useNavigate();

  const onSubmit = async(e) => {
    e.preventDefault()
    try {
      const body = {postid: pid.id, title: values.title, body: values.body};
      console.log(body);

      const response = await fetch(`http://localhost:5000/editPost?postid=${pid.id}`, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
          token: localStorage.token,
        },
        body: JSON.stringify(body)
      });

      await response.json();
      navigate(`/question/${pid.id}`);
    } catch (err) {
      console.error(err.message);
    }
  }

  return (
    <Fragment>
      <input className="form-control my-3" name="title" type="text" value = {values.title} onChange={(e) => {setValues({...values, [e.target.name]: e.target.value});}} placeholder="title"/>
      <textarea className="form-control my-3" name="body" value = {values.body} onChange={onBodyChange} placeholder="body"/>
      <button className="btn btn-primary" onClick={onSubmit}>Post</button>
    </Fragment>
  )
}

export default PostEditor;


// import React, { Fragment, useEffect, useState } from "react";
// import { useNavigate } from "react-router-dom";
// import { useParams } from "react-router-dom";
// const parsehtml = require("html-react-parser");

// function PostEditor() {
//   const initialValues = {
//     title: "",
//     body: "",
//   };

//   const pid = useParams();
//   const [values, setValues] = useState(initialValues);

//   const {title, tags, body} = values;

//   const onBodyChange = (e) => {
//     const newValue = e.target.name === "body" ? parsehtml(e.target.value) : e.target.value;
//     setValues({...values, [e.target.name]: newValue});
//   }

//   const navigate = useNavigate();

//   const onSubmit = async(e) => {
//     e.preventDefault()
//     try {
//       const body = {postid: pid, tags: values.tags, body: values.body};

//       const response = await fetch(`http://localhost:5000/editPost?postid=${pid.postid}`, {
//         method: "POST",
//         headers: {
//           "Content-Type": "application/json",
//           token: localStorage.token,
//         },
//         body: JSON.stringify(body)
//       });

//       const data = await response.json();
//       setValues(data);
//       navigate(`/view/${pid.postid}`);
//     } catch (err) {
//       console.error(err.message);
//     }
//   }

//   return (
//     <Fragment>
//       <input className="form-control my-3" name="title" type="text" value = {values.title} onChange={(e) => {setValues({...values, [e.target.name]: e.target.value});}} placeholder="title"/>
//       <textarea className="form-control my-3" name="body" value = {values.body} onChange={onBodyChange} placeholder="body"/>
//       <button className="btn btn-primary" onClick={onSubmit}>Post</button>
//     </Fragment>
//   )
// }

// export default PostEditor;


// import React, { Fragment, useEffect, useState } from "react";
// import { useNavigate } from "react-router-dom";
// import { useParams } from "react-router-dom";
// const parsehtml = require("html-react-parser");

// function PostEditor() {
//   const initialValues = {
//     title: "",
//     body: "",
//   };

//   const pid = useParams();
//   const [values, setValues] = useState(initialValues);

//   const {title, tags, body} = values;

//   const onChange = (e) => {
//     setValues({...values, [e.target.name]: e.target.value});
//   }

//   const navigate = useNavigate();

//   const onSubmit = async(e) => {
//     e.preventDefault()
//     try {
//       const body = {postid: pid, tags: values.tags, body: values.body};

//       const response = await fetch(`http://localhost:5000/editPost?postid=${pid.postid}`, {
//         method: "POST",
//         headers: {
//           "Content-Type": "application/json",
//           token: localStorage.token,
//         },
//         body: JSON.stringify(body)
//       });

//       const data = await response.json();
//       setValues(data);
//       navigate(`/view/${pid.postid}`);
//     } catch (err) {
//       console.error(err.message);
//     }
//   }

//   return (
//     <Fragment>
//       <input className="form-control my-3" name="title" type="text" value = {values.title} onChange={(e) => {setValues({...values, [e.target.name]: e.target.value});}} placeholder="title"/>
//       <textarea className="form-control my-3" name="body" type="text" value = {values.body} onChange={(e) => {setValues({...values, [e.target.name]: e.target.value});}} placeholder="body"/>
//       <button className="btn btn-primary" onClick={onSubmit}>Post</button>
//       </Fragment>
//   )
// }

// export default PostEditor;