<?php

function __psb_mega_menu() {
	/**
	 * We have fairly complicated markup requirements for our primary nav mega
	 * menu. In particular we need different markup on each of the three
	 * different levels:
	 *
	 * level one: icon ("P"), name ("Patents"), description and "learn more"
	 * level two: div wrapper so we can float three side by side
	 * level three: plain link
	 *
	 * theme_menu_tree() and theme_menu_link() won't work since there's no way
	 * to work out what level of the tree we're in for either of those hooks.
	 *
	 * menu_tree_page_data() only expands a menu link if it's set to be
	 * expanded, and we want the primary nav 100% expanded regardless of that
	 * setting.
	 *
	 * We can't use hook_menu_block_tree_alter(), since that runs before
	 * menu_block_tree_output() which will overwrite any #theme we set.
	 *
	 * So we call menu_block.module:menu_tree_build(). they do encourage this
	 * - "developers can use the API of this module to create their own menu
	 * trees outside the confines of blocks" - but it makes this theme
	 * dependent on the menu_block module (which is included out of the box
	 * for govcms so should be fine).
	 */
	$menu_name = variable_get('menu_main_links_source', 'main-menu');
	$config = array(
		'delta' => 'mega_menu',
		'menu_name' => $menu_name,
		'parent_mlid' => 0,
		'title_link' => 0,
		'level' => 1,
		'follow' => 0,
		'depth' => 3,
		'depth_relative' => 0,
		'expanded' => TRUE,
		'sort' => FALSE
	);
	$tree = menu_tree_build($config);
	$tree_content = $tree['content']['#content'];
	__psb_add_mega_menu_theme_suggestions($tree_content);
	return $tree_content;
}

function __psb_add_mega_menu_theme_suggestions(&$tree, $level = 1)  {
	foreach (element_children($tree) as $key) {
		$value = &$tree[$key];
		array_unshift($value['#theme'], 'menu_link__menu_block__mega_menu__level_' . $level);
		if (isset($value['#localized_options']['attributes']['class'])) {
			// Merge our classes on the menu link <a> tag
			// (#localized_options->attributes->class) up onto the <li> tag
			// (#attributes->class). The menu attributes module lets us add
			// classes to menu links, but we actually need them on the <li> so
			// that we can style e.g. the "search patents" and "apply for a
			// patent" menus per the design.
			$value['#attributes']['class'] = array_merge($value['#attributes']['class'], $value['#localized_options']['attributes']['class']);
		}
		if (!empty($value['#below'])) {
			__psb_add_mega_menu_theme_suggestions($value['#below'], $level + 1);
		}
	}
	if (!empty($tree['#theme_wrappers'])) {
		array_unshift($tree['#theme_wrappers'][0], 'menu_tree__menu_block__mega_menu__level_' . $level);
	}
}

/**
 * Implements theme_menu_link().
 */
function psb_menu_link__menu_block__mega_menu__level_1(array $variables) {
	$element = $variables['element'];

	if ($element['#href'] == '<front>') {
		// special case for the homepage
		array_push($element['#attributes']['class'], 'icon', 'icon-home');
		$output = l($element['#title'], $element['#href'], $element['#localized_options']);
		return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . "</li>\n";
	}
	else {
		$tab_id = $element['#original_link']['mlid'];
		$class = drupal_clean_css_identifier(strtolower($element["#title"]));
		// get tab header
		$tab_header = l(
			$element['#title'], 
			$element['#href'], 
			array_merge_recursive(
				$element['#localized_options'],
				array(
					'attributes' => array(
						'data-toggle' => 'dropdown',
						'data-tab-id' => $tab_id,
						'class' => array('title', 'dropdown-toggle', 'megamenu-tab-' . $class)
					)
				)
			)
		);
		// get tab contents
		$tab_contents = '';
		{
			$sub_menu = '';
			if ($element['#below']) {
				$sub_menu = drupal_render($element['#below']);
			}
			$title = l(
				$element['#title'], 
				$element['#href'], 
				array_merge_recursive($element['#localized_options'], array('attributes' => array('class' => array('title'))))
			);
			// using <i> for icons per bootstrap convention
			$icon = '<i class="icon icon-' . $class . '"></i>';
			$learn_more = l(
				t('Learn more'),
				$element['#href'],
				array_merge_recursive($element['#localized_options'], array('attributes' => array('class' => array('learn-more'))))
			);
			$description = 
				!empty($element['#localized_options']['attributes']['title'])
				? '<p>' . $element['#localized_options']['attributes']['title'] . '</p>'
				: '';
			$tab_contents = 
				'<div class="megamenu-tab-contents dropdown-menu" data-tab-id="' . $tab_id . '">' .
					$icon .
					'<div class="megamenu-tab-contents__title">' . $title . $description . '</div>' .
					$learn_more .
					$sub_menu . 
					'<div class="clearfix" />' .
				'</div>';
		}
		$output = $tab_header . $tab_contents;
		return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . "</li>\n";
	}
}

/**
 * Implements theme_menu_link().
 */
function psb_menu_link__menu_block__mega_menu__level_2(array $variables) {
	$element = $variables['element'];
	$sub_menu = '';

	if ($element['#below']) {
		$sub_menu = drupal_render($element['#below']);
	}
	$output = l($element['#title'], $element['#href'], $element['#localized_options']);
	return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements theme_menu_link().
 */
function psb_menu_link__menu_block__mega_menu__level_3(array $variables) {
	$element = $variables['element'];
	$sub_menu = '';

	if ($element['#below']) {
		$sub_menu = drupal_render($element['#below']);
	}
	$output = l($element['#title'], $element['#href'], $element['#localized_options']);
	return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements theme_menu_tree().
 */
function psb_menu_tree__menu_block__mega_menu__level_1($variables) {
	return '<ul class="menu megamenu megamenu-level-1 nav nav-tabs">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree().
 */
function psb_menu_tree__menu_block__mega_menu__level_2($variables) {
	return '<ul class="menu megamenu megamenu-level-2">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_tree().
 */
function psb_menu_tree__menu_block__mega_menu__level_3($variables) {
	return '<ul class="menu megamenu megamenu-level-3">' . $variables['tree'] . '</ul>';
}
