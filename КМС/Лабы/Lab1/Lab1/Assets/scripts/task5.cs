using System.Collections;
using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using UnityEngine;

public class task5 : MonoBehaviour
{
    private Color[] colors = new Color[] 
    {
        Color.red,
        Color.green, 
        Color.blue,
        Color.white,
        Color.yellow
    };

    public float speed = 5f;
    private Rigidbody rb;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();      
    }

    // Update is called once per frame
    void Update()
    {
        float moveHorizontal = Input.GetAxis("Horizontal");
        float moveVertical = Input.GetAxis("Vertical");

        Vector3 movement = new Vector3(moveHorizontal, 0.0f, moveVertical);
        rb.AddForce(movement * speed);

        if (Input.GetKey(KeyCode.Space))
        {
            rb.AddForce(0, 5f, 0);
        }

        if (Input.anyKeyDown)
        {  
            GetComponent<Renderer>().material.color = colors[new System.Random().Next(0 , colors.Length)];
        }       
    }


}
