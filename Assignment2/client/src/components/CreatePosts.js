import React, { Fragment, useEffect, useState } from "react";
import {Link} from "react-router-dom";

const CreatePosts = () => {
    const [inputs, setInputs] = useState({
        
    })

    return (
        <Fragment>
            <h1 className="text-center my-5">Create Post</h1>
            <form>
                <input type = "text" name = "title" placeholder="Title" className="form-control my-3" value = {inputs.title}/>
            </form>
        </Fragment>
    )
}