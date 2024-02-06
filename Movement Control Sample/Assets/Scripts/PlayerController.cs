using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    [SerializeField] float speed;
    [SerializeField] float turnSpeed;
    [SerializeField] float jumpForce;
    [SerializeField] float gravityModifier;

    private float verticalInput;
    private float horizontalInput;
    private Rigidbody playerRb;
    private bool ableToJump = true;
    // Start is called before the first frame update
    void Start()
    {
        playerRb = GetComponent<Rigidbody>();
        Physics.gravity *= gravityModifier; // supaya jatuhnya lebih cepat
    }

    // Update is called once per frame
    void Update()
    {
        // bagian gerakan maju-mundur-kanan-kiri
        verticalInput = Input.GetAxis("Vertical");
        horizontalInput = Input.GetAxis("Horizontal");
        Vector3 arah = new Vector3(horizontalInput, 0, verticalInput).normalized; // supaya kecepatannya sama untuk semua arah
        transform.Translate(arah * speed * Time.deltaTime);

        // lompat
        if (Input.GetKeyDown(KeyCode.Space) && ableToJump) // tekan spasi untuk lompat
        {
            playerRb.AddForce(Vector3.up * jumpForce, ForceMode.Impulse);
            ableToJump = false; // supaya tidak bisa lompat di udara
        }

        // tengok kanan-kiri
        float turnInput = Input.GetAxis("Mouse X");
        transform.Rotate(Vector3.up * turnInput * turnSpeed * Time.deltaTime);
    }

    private void OnCollisionEnter(Collision collision)
    {
        ableToJump = true; // bisa lompat ketika menyentuh objek lain
    }
}
