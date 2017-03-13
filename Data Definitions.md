#Data Definition
This file explains how password data is managed and stored on disk.

##Data on Disk
Password data is stored on disk as encrypted JSON. It's encrypted using AES256 in cbc mode. We are using OpenSSL library for encrypting the file.

##JSON Format
We are using JSON because it is flexible and allows us for future extensions. Unencrypted JSON never gets written to disk and only stayes in RAM. Here is an example of a JSON file:

```
{
  "items": [
    {
      "name": "Google",
      "fields": [
        {
          "name": "Username",
          "type": "username",
          "value": "open_user",
          "sensitive": false
        },
        {
          "name": "Password",
          "type": "password",
          "value": "secret_pa55",
          "sensitive": true
        }
      ]
    },
    {
      "name": "Firefox",
      "fields": [
        {
          "name": "E-mail",
          "type": "email",
          "value": "electron.pass@mail.com",
          "sensitive": false
        },
        {
          "name": "Password",
          "type": "password",
          "value": "reallynotsecurepass123",
          "sensitive": true
        }
      ]
    }
  ]
}

```

Items is array of passwords that user has stored. Each item has a ```name``` field which is a display name for the field. It also has a ```fields``` attribute which is an array of fields for the entry. Each field has 3 properties:

- ```name``` represents a display name, that is shown to the user
- ```type``` represents a field type. Types are explained in the next section of this document
- ```value``` represents the data that is stored in this field (for instance: the password itself)
- ```sensitive``` is a boolean that marks if the field's value should be hidden and only displayed with dots, unless the user explicitly requests to see the value

##Types
Type of the field is used to enhance the user experiance. It will probably not be used by the core library, but the applications will use it to show additional information to the user.

Currently possible types are:

- ```username``` for storing usernames
- ```password``` for storing passwords
- ```email``` for storing email addresses
- ```url``` for storing on which webpage the password entry is used
- ```pin``` for storing numeric values only