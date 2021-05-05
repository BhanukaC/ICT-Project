import 'package:flutter/material.dart';
import 'package:flash_chat/components/rounded_button.dart';
import 'package:flash_chat/constants.dart';
import 'package:firebase_database/firebase_database.dart';

import 'package:modal_progress_hud/modal_progress_hud.dart';

class RegistrationScreen extends StatefulWidget {
  static const String id = 'registration_screen';
  @override
  _RegistrationScreenState createState() => _RegistrationScreenState();
}

class _RegistrationScreenState extends State<RegistrationScreen> {
  final DatabaseReference db = FirebaseDatabase.instance.reference();
  bool showSpinner = false;
  String user;
  String balance;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Top Up"),
      ),
      backgroundColor: Colors.white,
      body: ModalProgressHUD(
        inAsyncCall: showSpinner,
        child: Padding(
          padding: EdgeInsets.symmetric(horizontal: 24.0),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.stretch,
            children: <Widget>[
              TextField(
                keyboardType: TextInputType.emailAddress,
                textAlign: TextAlign.center,
                onChanged: (value) {
                  user = value;
                },
                decoration:
                    kTextFieldDecoration.copyWith(hintText: 'Enter user Name'),
              ),
              SizedBox(
                height: 8.0,
              ),
              TextField(
                textAlign: TextAlign.center,
                onChanged: (value) {
                  balance = value;
                },
                decoration: kTextFieldDecoration.copyWith(
                    hintText: 'Enter your balance'),
              ),
              SizedBox(
                height: 24.0,
              ),
              RoundedButton(
                title: 'Top Up',
                colour: Colors.blueAccent,
                onPressed: () async {
                  db
                      .child("Customers")
                      .child(user.toString())
                      .update({"balance": balance});
                },
              ),
            ],
          ),
        ),
      ),
    );
  }
}
