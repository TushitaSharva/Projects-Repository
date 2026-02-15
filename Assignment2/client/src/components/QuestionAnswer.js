import React, { Fragment, useState, useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { useParams } from "react-router-dom";
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faArrowAltCircleUp, faArrowAltCircleDown, faReply} from '@fortawesome/fontawesome-free-solid';

const parsehtml = require("html-react-parser");

export default function QuestionAnswer() {
    const [posts, setPosts] = useState([]);

    const pid = useParams();
    
    async function questionAnswer() {
        const response = await fetch(`http://localhost:5000/question?postid=${pid.postid}`, {
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
          console.log("Failed to fetch that post");
        }
    }

    useEffect(() => {
        questionAnswer();
    }, []);

    const navigate = useNavigate();
    const onClickReply = async (e) => {
        navigate(`/replyPost/${pid.postid}`);
    }

    const handleUpvote = async(e, postid, ownerid) => {
      e.preventDefault()

      const body = {post_id: postid, owner_id: ownerid, action: 1}

      try {
        const response = await fetch(`http://localhost:5000/vote`, {
          method: "POST",
          headers: {
            "Content-Type" : "application/json",
            token: localStorage.token,
          },
          body: JSON.stringify(body)
        })

        const data = await response.json();
        setPosts(posts.map(post=>post.id === data.id ? data : post));
      } catch (err) {
        console.error(err.message);
      }
    }

    const handleDownvote = async(e, postid, ownerid) => {
      e.preventDefault()
      
      const body = {post_id: postid, owner_id: ownerid, action: 0}

      try {
        const response = await fetch(`http://localhost:5000/vote`, {
          method: "POST",
          headers: {
            "Content-Type" : "application/json",
            token: localStorage.token,
          },
          body: JSON.stringify(body)
        })

        const data = await response.json();
        setPosts(posts.map(post=>post.id === data.id ? data : post))
      } catch (err) {
        console.error(err.message);
      }
    }
    
    return (
      <Fragment>
        <h1 className="post-header">Post #{pid.postid} <button className="btn btn-primary" onClick={onClickReply}> <FontAwesomeIcon icon={faReply} />  Reply</button></h1>
        {posts.length ? (
          <ul style={{listStyleType: 'none', overflow: 'hidden'}}>
            {posts.map((post) => (
              <li key={post.id} style={{border: "1px solid white", padding: "10px"}}>
                <div style={{display: 'flex'}}>
                  <div style={{display: 'flex', flexDirection: 'column', justifyContent: 'center', marginRight: '16px'}}>
                    <button className="btn btn-primary" onClick={e => handleUpvote(e, post.id, post.owner_user_id)}> <FontAwesomeIcon icon={faArrowAltCircleUp} /></button>
                    <span style={{textAlign: 'center'}}>{post.score}</span>
                    <button className="btn btn-primary" onClick={e => handleDownvote(e, post.id, post.owner_user_id)}> <FontAwesomeIcon icon={faArrowAltCircleDown} /></button>
                  </div>
                  <div>
                    <h5>{post.title} - {post.owner_name}</h5>
                    <div dangerouslySetInnerHTML={{__html: post.body.replace(/<code>(.*?)<\/code>/gs, '<span class="code">$1</span>')}}></div>
                  </div>
                </div>
              </li>
            ))}
          </ul>
        ) : (
          <p>Loading...</p>
        )}
        <style>{`
          .code {
            padding: 10px;
            border-radius: 5px;
            color: lightblue;
            overflow-x: hidden;
          }
        `}</style>
      </Fragment>
    );
    
    
}