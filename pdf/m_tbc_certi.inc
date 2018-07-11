<?php
function m_tbc_certificate_participation_form($form, &$form_state)
	{
		$form['name_title'] = array(
				'#type' => 'select',
				'#title' => t('Title'),
				'#options' => array(
						'Dr.' => 'Dr.',
						'Prof.' => 'Prof.',
						'Mr.' => 'Mr.',
						'Mrs.' => 'Mrs.',
						'Ms.' => 'Ms.'
				),
				'#required' => TRUE
		);
		$form['name'] = array(
				'#type' => 'textfield',
				'#title' => t('Name of Participant'),
				'#maxlength' => 50,
				'#required' => TRUE
		);
		$form['email_id'] = array(
				'#type' => 'textfield',
				'#title' => t('Email'),
				'#size' => 50,
				'#default_value' => 'Not availbale'
		);
		$form['institute_name'] = array(
				'#type' => 'textfield',
				'#title' => t('Collage / Institue Name'),
				'#required' => TRUE
		);
		$form['institute_address'] = array(
				'#type' => 'textfield',
				'#title' => t('Collage / Institue address'),
				'#required' => TRUE
		);
		$form['book_name'] = array(
				'#type' => 'textfield',
				'#title' => t('Book name'),
				'#required' => TRUE
		);
		$form['author'] = array(              
				'#type' => 'textfield',
				'#title' => t('author'),
				'#required' => True
                );
		$form['department'] = array(
				'#type' => 'textfield',
				'#title' => t('Department'),
				'#required' => TRUE
		);
		$form['proposal_id'] = array(
				'#type' => 'textfield',
				'#title' => t('Book Proposal Id'),
				'#required' => TRUE
		);
		$form['pref_id'] = array(
				'#type' => 'textfield',
				'#title' => t('Book Preference Id'),
				'#required' => TRUE
		);
		$form['submit'] = array(
				'#type' => 'submit',
				'#value' => t('Submit')
		);
		return $form;
	}
function m_tbc_certificate_participation_form_submit($form, &$form_state)
	{
		global $user;
		$v = $form_state["values"];
		$result = "INSERT INTO {m_tbc_certificate} 
    (uid, name_title, name, email_id, institute_name, institute_address, book_name, department, author,proposal_id,pref_id,type,creation_date) VALUES
    (:uid, :name_title, :name, :email_id, :institute_name, :institute_address, 
    :book_name, :department, :author,:proposal_id,:pref_id,:type,:creation_date)";
		$args = array(
				":uid" => $user->uid,
				":name_title" => trim($v['name_title']),
				":name" => trim($v['name']),
				":email_id" => trim($v['email_id']),
				":institute_name" => trim($v['institute_name']),
				":institute_address" => trim($v['institute_address']),
				":book_name" => trim($v['book_name']),
				":author" => trim($v['author']),
				":department" => trim($v['department']),
				":proposal_id" => $v['proposal_id'],
				":pref_id" => $v['pref_id'],
				":type" => "Participant",
				":creation_date" => time()
		);
		$proposal_id = db_query($result, $args);
		drupal_goto('m_tbc/certificate');
	}
/******** edit participation *********/
function m_tbc_certificate_participation_edit_form($form, &$form_state)
	{
		$type = arg(2);
		$action = arg(4);
		$proposal_id = arg(5);
		$certi_id = arg(6);
		if ($type == "tbc_participation" && $action == "edit")
			{
				$query = db_query("SELECT * FROM m_tbc_certificate WHERE proposal_id=:prop_id AND id=:certi_id", array(
						":prop_id" => $proposal_id,
						":certi_id" => $certi_id
				));
				$details_list = $query->fetchobject();
				if ($details_list->type == "Participant")
					{
						$form['name_title'] = array(
								'#type' => 'select',
								'#title' => t('Title'),
								'#options' => array(
										'Dr.' => 'Dr.',
										'Prof.' => 'Prof.',
										'Mr.' => 'Mr.',
										'Mrs.' => 'Mrs.',
										'Ms.'=> 'Ms.'
								),
								'#default_value' => $details_list->name_title
						);
						$form['name'] = array(
								'#type' => 'textfield',
								'#title' => t('Name of Participant'),
								'#maxlength' => 50,
								'#default_value' => $details_list->name
						);
						$form['email_id'] = array(
								'#type' => 'textfield',
								'#title' => t('Email'),
								'#size' => 50,
								'#default_value' => $details_list->email_id
						);
						$form['institute_name'] = array(
								'#type' => 'textfield',
								'#title' => t('Collage / Institue Name'),
								'#default_value' => $details_list->institute_name
						);
						$form['institute_address'] = array(
								'#type' => 'textfield',
								'#title' => t('Collage / Institue address'),
								'#default_value' => $details_list->institute_address
						);
						$form['book_name'] = array(
								'#type' => 'textfield',
								'#title' => t('Lab name'),
								'#default_value' => $details_list->book_name
						);
						$form['author'] = array(
								'#type' => 'textfield',
								'#title' => t('author'),
								'#default_value' => $details_list->author
						);
						$form['department'] = array(
								'#type' => 'textfield',
								'#title' => t('Department'),
								'#default_value' => $details_list->department
						);
						
						$form['proposal_id'] = array(
								'#type' => 'textfield',
								'#title' => t('Book Proposal Id'),
								'#default_value' => $details_list->proposal_id
						);
						$form['pref_id'] = array(
								'#type' => 'textfield',
								'#title' => t('Book Preference Id'),
								'#default_value' => $details_list->pref_id
						);
						$form['certi_id'] = array(
								'#type' => 'hidden',
								'#default_value' => $details_list->id
						);
						$form['submit'] = array(
								'#type' => 'submit',
								'#value' => t('Submit')
						);
					} //$details_list->type == "Participant"
				else
					{
						$form['err_message'] = array(
								'#type' => 'item',
								'#title' => t('Message'),
								'#markup' => 'Invalid information'
						);
					}
			} //$type == "lm_participation" && $action == "edit"
		else
			{
				$form['err_message'] = array(
						'#type' => 'item',
						'#title' => t('Message'),
						'#markup' => 'Invalid information'
				);
			}
		return $form;
	}
function m_tbc_certificate_participation_edit_form_submit($form, &$form_state)
	{
		global $user;
		$v = $form_state["values"];
		$result = "UPDATE m_tbc_certificate SET
    uid=:uid, 
    name_title=:name_title, 
    name=:name, 
    email_id=:email_id, 
    institute_name=:institute_name, 
    institute_address=:institute_address, 
    book_name=:book_name,
    author=:author,
    department=:department,
    proposal_id=:proposal_id,
    pref_id=:pref_id,
    type=:type,
    creation_date=:creation_date
    WHERE id=:certi_id";
		$args = array(
				":uid" => $user->uid,
				":name_title" => trim($v['name_title']),
				":name" => trim($v['name']),
				":email_id" => trim($v['email_id']),
				":institute_name" => trim($v['institute_name']),
				":institute_address" => trim($v['institute_address']),
				":book_name" => trim($v['book_name']),
				":author" => trim($v['author']),
				":department" => trim($v['department']),
				":proposal_id" => trim($v['proposal_id']),
				":pref_id" => trim($v['pref_id']),
				":type" => "Participant",
				":creation_date" => time(),
				":certi_id" => $v['certi_id']
		);
		$proposal_id = db_query($result, $args);
		drupal_goto('m_tbc/certificate');
	}
/*************************************/
function _list_all_m_tbc_certificates()
	{
		$query = db_query("SELECT * FROM m_tbc_certificate");
		$search_rows = array();
		$output = '';
		$details_list = $query->fetchAll();
		foreach ($details_list as $details)
			{
				if ($details->type == "Proposer")
					{
						$search_rows[] = array(
								$details->book_name,
								$details->institute_name,
								$details->name,
								$details->type,
								l('Download Certificate', 'm_tbc/certificate/generate_pdf/' . $details->proposal_id . '/' . $details->id),
								l('Edit Certificate', 'm_tbc/certificate/generate_pdf/tbc_proposer/form/edit/' . $details->proposal_id . '/' . $details->id)
						);
					} //$details->type == "Proposer"
				else
					{
						$search_rows[] = array(
								$details->book_name,
								$details->institute_name,
								$details->name,
								$details->type,
								l('Download Certificate', 'm_tbc/certificate/generate_pdf/' . $details->proposal_id . '/' . $details->id),
								l('Edit Certificate', 'm_tbc/certificate/tbc_participation/form/edit/' . $details->proposal_id . '/' . $details->id)
						);
					}
			} //$details_list as $details
		$search_header = array(
				'Book Name',
				'Institute name',
				'Name',
				'Type',
				'Download Certificates'
		);
		$output .= theme('table', array(
				'header' => $search_header,
				'rows' => $search_rows
		));
		return $output;
	}
