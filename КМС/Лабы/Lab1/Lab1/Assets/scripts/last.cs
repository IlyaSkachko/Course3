using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UIElements;

public class last : MonoBehaviour
{

    public MeshRenderer render;
    // Start is called before the first frame update
    void Start()
    {
        render = gameObject.GetComponent<MeshRenderer>();
    }

    // Update is called once per frame
    void Update()
    {
        float minX = render.bounds.min.x;
        float maxX = render.bounds.max.x;
        float minZ = render.bounds.min.z;
        float maxZ = render.bounds.max.z;

        float newX = Random.Range(minX, maxX);
        float newZ = Random.Range(minZ, maxZ);

        float newY = gameObject.transform.position.y + new System.Random().Next(1, 20);

        if (Input.GetMouseButtonDown(0))
        {
            var cube = GameObject.CreatePrimitive(PrimitiveType.Cube);

            cube.transform.position = new Vector3 (newX, newY, newZ);
            

            Renderer renderer = cube.GetComponent<Renderer>();
            renderer.material.color = new Color(Random.value, Random.value, Random.value);

            cube.AddComponent<Rigidbody>();
        }

    }
}
