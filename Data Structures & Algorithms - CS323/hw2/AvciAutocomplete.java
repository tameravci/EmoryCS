/*
 * Copyright 2014, Emory University
 * Author: Tamer Avci CS323
 */
package trie;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import trie.Trie;
import utils.LengthComparator;

public class AvciAutocomplete extends Trie<List<String>> implements IAutocomplete<List<String>>
{
	@Override
	public List<String> getCandidates(String prefix)
	{
		List<String> list = new ArrayList<String>();
		TrieNode<List<String>> node = find(prefix);
		if (node==null)
			return list;
		Comparator<String> comp = (Comparator<String>) new LengthComparator();
		traverse(node, prefix, list);
		Collections.sort(list, comp);
		
		if(node.hasValue()) {
			list.removeAll(node.getValue());
			list.addAll(0, node.getValue());
		}
		
		if (list.size() > 20)
			list = list.subList(0, 20);
				
		return list;
	}
	
	private void traverse(TrieNode<List<String>> node, String prefix, List<String> list) {
		if (node.isEndState())				
			list.add(prefix);
		
		for(Character key: node.getChildrenMap().keySet())
			traverse(node.getChildrenMap().get(key), prefix+key, list);
		
	}

	@Override
	public void pickCandidate(String prefix, String candidate)
	{
		TrieNode<List<String>> node = find(prefix);
		List<String> list = new ArrayList<String>();
		
		if (find(prefix)== null && candidate.startsWith(prefix)) {  //for the rare case: if the prefix does not have any recommendations but you still want to add a word, this case prefix must be added as a word to avoid nullpointer
			put(candidate, null);
			put(prefix, null); node=find(prefix);
		}

		
		if (candidate.startsWith(prefix)) 
		{
			put(candidate, null);
			if(node.hasValue()) 
			{
				if(node.getValue().contains(candidate))
					node.getValue().remove(candidate);
				node.getValue().add(0, candidate);
				return;
			}
			list.add(0, candidate);
			node.setValue(list);
		}
		else 
		{
			System.out.println("This is not what you intended to type");
			return;
		}
	}
}